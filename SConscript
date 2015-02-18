import os
import platform

from SCons.Script import AddOption
from SCons.Node import NodeList

# if we're cross-compiling for birdwing, we need to explicitly set the
# Environment platform to 'posix' to have the correct params passed to gcc/ld
# when the system hosting the cc is something other than linux (e.g. darwin)
platform_args = {}
if os.environ.get('MBCOREUTILS_BIRDWING') and not \
        os.environ.get('BW_NATIVE_BUILD'):
    platform_args['platform'] = 'posix'

env = Environment(
    ENV=os.environ,
    tools=['default', 'mb_install',
           'mustache_codegen'],
    toolpath=['#../mw-scons-tools',
              'site_scons',
              os.environ.setdefault('BWSCONSTOOLS_PATH',
                                    '#/../bw-scons-tools')],
    **platform_args)

# MBRecursiveFileGlob is defined in both the mb_install tool, and the
# birdwing_install tool, and both implementations work slightly differently.
# We always want to use the one from mb_install, so grab it here before the
# birdwing_install tool is loaded.
_recursive_file_glob = env.MBRecursiveFileGlob

# -- Mustache-based codegen stuff -- #

if 'MBCOREUTILS_BIRDWING' in os.environ:
    # If we're building for birdwing, pull in the birdwing_install
    # tool so default arguments like 'machine' are properly initialized.
    env.Tool('birdwing_install')
else:
    AddOption('--machine', dest='machine')

BWCGEN_ROOT_DIR = 'birdwing_codegen'
BWCGEN_OUTPUT_DIR = 'birdwing'

machine = None

try:
    if os.path.isdir(os.environ['BWSCONSTOOLS_PATH']):
        env.Tool('birdwing_settingsgen')
        machine = GetOption('machine')
except AttributeError, ImportError:
    print("error")
    pass

if machine:
    # We're building birdwing firmware for a specific machine, so have to
    # do machine specific code-generation based off the
    # printer_settings.json file for that machine.  Birdwing-Software gets
    # built after MBCoreUtils, so we have to generate the right
    # printer_settings.json file here too. This is so hacky but I don't see
    # any less hacky way of doing it that doesn't require big refactors. :(
    env['MBCOREUTILS_BWMACHINE_SETTINGS'] = os.path.join(
        str(Dir("#/")),
        'obj',
        BWCGEN_OUTPUT_DIR,
        'printer_settings.json'
    )
    env.BWGenSettings('printer_settings.json',
                      env['MBCOREUTILS_BWMACHINE_SETTINGS'])
else:
    print('[WARNING] Mustache Codegen: Not building for a specific machine'
          ', codegen output will be missing machine-specific components.')


# Declare the machine-specific settings file as an external source
# if we're doing codegen for a specific bot.  That way, templates will
# be re-rendered if the settings file changes.
external_sources = [env['MBCOREUTILS_BWMACHINE_SETTINGS']] if machine else None

# Used in multiple places so might as well define it here
templates_dir = os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, 'templates')

# Do the code gen.
env.MustacheCodegen(context_dir=os.path.join(str(Dir("#/")),
                                             BWCGEN_ROOT_DIR,
                                             'contexts'),
                    template_dir=templates_dir,
                    out_dir=os.path.join(str(Dir("#/")),
                                         'obj',
                                         BWCGEN_OUTPUT_DIR),
                    transformations_file=os.path.join(str(Dir("#/")),
                                                      BWCGEN_ROOT_DIR,
                                                      'transformations.json'),
                    ext_deps=external_sources)


if ("MBCOREUTILS_BIRDWING" in os.environ) or env.MBIsLinux() or env.MBIsMac():
    # Add an empty command that makes the top-level directory target
    # depend on the header files. This ensures the static header files
    # are copied into the variant dir.
    env.Command('.', _recursive_file_glob('include', '*.h'), '')

    copyto = os.path.join(str(Dir("#/")),
                          'obj',
                          'include',
                          'bwcoreutils')
else:
    copyto = os.path.join(str(Dir("#/")),
                          'include',
                          'bwcoreutils')

# Hack to copy codegen'd cpp files from obj/birdwing/shared_cpp to
# the include/bwcoreutils directorty. This is necessary since a bunch
# of projects already expect shared cpp birdwing headers to be there.
# TODO(jacksonh) - remove this awful hack
copyfrom = os.path.join(str(Dir("#/")),
                        'obj',
                        BWCGEN_OUTPUT_DIR,
                        'shared_cpp')
for header in os.listdir(os.path.join(templates_dir, 'shared_cpp')):
    if header.endswith('.hh') or header.endswith('.h'):
        env.Command(
            os.path.join(copyto, os.path.basename(header)),
            os.path.join(copyfrom, os.path.basename(header)),
            Copy("$TARGET", "$SOURCE")
        )
# -- End Mustache-based codegen stuff -- #

#
# Swap out some things if we are building for birdwing or desktop.
# This could probably be handled more elegantly.
#
if ("MBCOREUTILS_BIRDWING" in os.environ):
    # This is here to prevent "cannot find target 'install'"  errors.
    # There may be a more logical thing to do with this alias
    path = os.path.join(str(Dir("#/")), 'obj', 'include')
    Alias("install", path)
else:
    # make_current_link=True is necessary for header-only libraries on mac
    env.MBInstallHeaders(env.Glob('include/mbcoreutils/*'),
                         'mbcoreutils', make_current_link=True)
    env.MBInstallHeaders(env.Glob('include/bwcoreutils/*'),
                         'bwcoreutils', make_current_link=True)
    if env.MBIsLinux():
        (distname, distversion, distid) = platform.linux_distribution()
        if 'Ubuntu' == distname:
            # On Ubuntu 12.04 we use GCC 4.8, which requires a c++ runtime
            # incompatible with the system default.
            # To make this work, we package the runtime library libstdc++6
            # from our jenkins slave in the package mb-libstdc++6 that
            # installs the library in /usr/lib/makerbot.
            # That directory is in the runpath for all of our executables,
            # so the OS will check it for libraries to laod before looking in
            # the system default directory.
            # For all other ubuntu versions, mb-libstdc++6 is an empty
            # package that installs nothing, allowing the OS to use the
            # default system runtime library as it normally would.
            def procfile(elem, fd):
                '''
                Write the paths of files or scons nodes from a nested list
                to a debian *.install file

                @param elem The current list, scons node, or path to write
                @param fd a file handle open for writing
                '''
                prefix = '/usr/lib/makerbot/'
                if isinstance(elem, list) or \
                        isinstance(elem, NodeList):
                    for el in elem:
                        procfile(el, fd)
                elif isinstance(elem, str):
                    fd.write(prefix + os.path.basename(elem) + '\n')
                else:
                    fd.write(prefix + os.path.basename(basepath(elem)) + '\n')

            def basepath(x):
                return File(x).srcnode().abspath

            if distversion == '12.04':
                # on 12.04 we must package the gcc 4.8 runtime
                stdcpplibsraw = Glob('/usr/lib/*-linux-gnu/libstdc++.so*')
                stdcpplibs = [elem for elem in stdcpplibsraw
                              if not os.path.islink(basepath(elem))]
                stdcpplibs = stdcpplibs[-1]
                stdcpptargets = env.MBInstallLib(stdcpplibs, None, 'makerbot')
                with open(basepath('#/debian/mb-libstdc++6.install'),
                          'w') as stdcppinstall:
                    procfile(stdcpptargets, stdcppinstall)
            else:
                # on other platforms this is empty package
                with open(basepath('#/debian/mb-libstdc++6.install'),
                          'w') as stdcppinstall:
                    stdcppinstall.write('\n')
    env.MBCreateInstallTarget()
