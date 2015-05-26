import os
import platform

from SCons.Script import AddOption
from SCons.Node import NodeList

os.environ.setdefault('BWSCONSTOOLS_PATH', '#/../bw-scons-tools')

env = Environment(
    ENV=os.environ,
    tools=['default', 'mb_install', 'mustache'],
    toolpath=['#../mw-scons-tools',
              "#Install/mw-scons-tools",
              '#/../mustache',
              '#/../bw-scons-tools'])

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

# For dynamic contexts
dynamic_context_args = {
    'APIGEN_PATH': os.path.join(
        os.pardir,
        os.pardir,
        'Birdwing-Software',
        'firmware',
        'kaiten',
        'api_docgen.py')
}

if 'MBCOREUTILS_BIRDWING' in os.environ:
    dynamic_context_args['MBCOREUTILS_BIRDWING'] = True

if 'MBCOREUTILS_BWMACHINE_SETTINGS' in env:
    dynamic_context_args['BWMACHINE_SETTINGS'] = (
        env['MBCOREUTILS_BWMACHINE_SETTINGS'])

templates_root = os.path.join(BWCGEN_ROOT_DIR, 'templates')
# I'm not sure that this file should be split up, but it does seem odd
# that it's shared by these three things
common_transformations_file = os.path.join(
    BWCGEN_ROOT_DIR, 'transformations.json')

outdir_base = Dir(os.path.join('#/obj', BWCGEN_OUTPUT_DIR)).abspath

# TODO(ted): all this explicitness is a little messy.
# Can I express the same thing in a cleaner way?

bwcodegen_contexts = env.Glob(os.path.join(BWCGEN_ROOT_DIR,
                                           'contexts', '*.py'))\
    + env.Glob(os.path.join(BWCGEN_ROOT_DIR,
                            'contexts', '*.json'))
# Do the code gen.
machine_cpp = env.MustacheCodegen(
    contexts=bwcodegen_contexts,
    templates=env.Glob(os.path.join(templates_root, 'machine_cpp', '*')),
    out_dir=os.path.join(outdir_base, 'machine_cpp'),
    transformations_file=common_transformations_file,
    dynamic_context_args=dynamic_context_args,
    ext_deps=external_sources)
shared_cpp = env.MustacheCodegen(
    contexts=bwcodegen_contexts,
    templates=env.Glob(os.path.join(templates_root, 'shared_cpp', '*')),
    out_dir=os.path.join(outdir_base, 'shared_cpp'),
    transformations_file=common_transformations_file,
    dynamic_context_args=dynamic_context_args,
    ext_deps=external_sources)
python_files = env.MustacheCodegen(
    contexts=bwcodegen_contexts,
    templates=env.Glob(os.path.join(templates_root, 'python', '*')),
    out_dir=os.path.join(outdir_base, 'python'),
    transformations_file=common_transformations_file,
    dynamic_context_args=dynamic_context_args,
    ext_deps=external_sources)

# The birdwing build system needs these to get built when the target is install
if ("MBCOREUTILS_BIRDWING" in os.environ):
    Alias("install", [machine_cpp, shared_cpp, python_files])


# Not sure if these are even needed in this location.
# Might be able to remove this and just install shared_cpp below.
shared_includes = []
for header in shared_cpp:
    shared_includes += env.Command(
        'include/bwcoreutils/${SOURCE.file}',
        header,
        Copy("$TARGET", "$SOURCE")
    )

# -- End Mustache-based codegen stuff -- #

#
# Swap out some things if we are building for birdwing or desktop.
# This could probably be handled more elegantly.
#
if ("MBCOREUTILS_BIRDWING" in os.environ):
    env.BWInstall('/usr/settings', Glob('#/birdwing_codegen/static/*'))
    # When our target is "install", we still need to build all
    # local files.  These files are still required by install
    # targets in other repositories.
    path = os.path.join(str(Dir("#/")), 'obj', 'include')
    Alias("install", path)
else:
    # make_current_link=True is necessary for header-only libraries on mac
    env.MBInstallHeaders(env.Glob('include/mbcoreutils/*'),
                         'mbcoreutils', make_current_link=True)
    env.MBInstallHeaders(shared_includes,
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
