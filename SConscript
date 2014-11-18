import os
from SCons.Script import AddOption

env = Environment(
    ENV=os.environ,
    tools=['default', 'mb_install',
           'mustache_codegen'],
    toolpath=['#../mw-scons-tools', 'site_scons', os.environ.setdefault('BWSCONSTOOLS_PATH',
                                                                        '#/../bw-scons-tools')])


### Mustache-based codegen stuff ###

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


# Hack to copy codegen'd cpp files from obj/birdwing/shared_cpp to
# obj/include/bwcoreutils. This is necessary since a bunch of projects already
# expect shared cpp birdwing headers to be there.
# TODO(jacksonh) - remove this awful hack
for header in os.listdir(os.path.join(templates_dir, 'shared_cpp')):
    if header.endswith('.hh') or header.endswith('.h'):
        env.Command(
            os.path.join(str(Dir("#/")),
                         'obj',
                         'include',
                         'bwcoreutils',
                         os.path.basename(header)),
            os.path.join(str(Dir("#/")),
                         'obj',
                         BWCGEN_OUTPUT_DIR,
                         'shared_cpp',
                         os.path.basename(header)),
            Copy("$TARGET", "$SOURCE")
        )

### End Mustache-based codegen stuff ###

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
    env.MBCreateInstallTarget()
