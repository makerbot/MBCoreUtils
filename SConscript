import mustache_based_codegen as mc
import machine_specific_settings_gen
import os
from SCons.Script import AddOption

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])


### Mustache-based codegen stuff ###

AddOption('--bwsoftware',
          dest='bwsoftware',
          type='string',
          default=os.path.join(str(Dir("#/")), '../../', 'Birdwing-Software'),
          help='Set Birdwing-Software repo location (if not ../../Birdwing-Software).')
AddOption('--machine', dest='machine')

BWCGEN_ROOT_DIR = 'birdwing_codegen'
BWCGEN_OUTPUT_DIR = 'birdwing'
bw_machine_settings_path = os.path.join(GetOption('bwsoftware'), 'firmware', 'settings')

env.Append(BUILDERS = {
    'birdwing_code_gen': Builder(action = mc.gen_files),
    'generate_machine_settings': Builder(action = machine_specific_settings_gen.gen_machine_specific_settings)
    })

try:
    machine = GetOption('machine')
except AttributeError:
    machine, machine_printer_settingsf = None, None
finally:
    if machine and os.path.exists(bw_machine_settings_path):
        # We're building birdwing firmware for a specific machine, so have to do
        # machine specific code-generation based off the printer_settings.json file for that machine.
        # Birdwing-Software gets built after MBCoreUtils, so we have to generate the right printer_settings.json
        # file here too. This is so hacky but I don't see any less hacky way of doing it that doesn't require big refactors. :(
        machine_printer_settingsf = [f for f in os.listdir(bw_machine_settings_path) if f == 'printer_settings.json.{0}'.format(machine)]
        if not machine_printer_settingsf:
            raise Exception('Unable to find printer_settings.json.{0}'.format(machine))
        env.generate_machine_settings(
            os.path.join(BWCGEN_OUTPUT_DIR, 'printer_settings.json'),
            [os.path.join(bw_machine_settings_path, 'printer_settings.json'), os.path.join(bw_machine_settings_path, machine_printer_settingsf[0])]
        )
        env['MBCOREUTILS_BWMACHINE_SETTINGS'] = os.path.join(str(Dir("#/")), 'obj', BWCGEN_OUTPUT_DIR, 'printer_settings.json')
    else:
        print('[WARNING] Mustache Codegen: Not building for a specific machine, codegen output will be missing machine-specific components.')

# List of template relative location strings, in the format <parent dir>/<filename>.
# This is done this way b/c parent dir has special meaning for codegen, see docs for more info.
# Used to construct both codegen source and target dicts.
os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME)
bw_template_files = [os.path.join(d, f) for d in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME))
                                        if os.path.isdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d))
                                        for f in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d))
                                        if os.path.isfile(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d, f))]

codegen_input_files = list(
        # Special file used to extend mustache's functionality. See docs.
        [os.path.join(BWCGEN_ROOT_DIR, mc.TRANSFORMATIONS_FILE),
        # Script to process transformations file & render templates.
        'site_scons/mustache_based_codegen.py'] +
        # Context json file(s) containing the data used to render templates.
        [os.path.join(BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME, f) for f in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME))
                                                               if os.path.isfile(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME, f)) and (f.endswith('.json') or f.endswith('.py'))] +
        # Template files to be rendered.
        [os.path.join(BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, relpath) for relpath in bw_template_files]
    )
if machine:
    # Machine-specific settings file (only if we're doing codegen for a specific bot)
    codegen_input_files += [os.path.join(str(Dir("#/")), 'obj', BWCGEN_OUTPUT_DIR, 'printer_settings.json')]

# these are the rendered templates - saved to <variantdir>/birdwing/<lang>/<file>
codegen_output_files = [os.path.join(BWCGEN_OUTPUT_DIR, relpath) for relpath in bw_template_files]

# Do the code gen.
env.birdwing_code_gen(codegen_output_files, codegen_input_files)

# Hack to copy codegen'd cpp files from obj/birdwing/cpp to obj/include/bwcoreutils,
# since a bunch of projects already expect shared cpp birdwing headers to be there.
# TODO(jacksonh) - remove this awful hack
for header in bw_template_files:
    if os.path.dirname(header) == 'cpp' and (header.endswith('.hh') or header.endswith('.h')):
        env.Command(
            os.path.join(str(Dir("#/")), 'obj', 'include', 'bwcoreutils', os.path.basename(header)),
            os.path.join(str(Dir("#/")), 'obj', BWCGEN_OUTPUT_DIR, 'cpp', os.path.basename(header)),
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
    # This is here to prevent "no such option" errors, need a better
    # solution. We don't actually use any of these.\
    # It would be a pain to include all of bw-scons-tools just for this,
    # but maybe that is the way to go.
    AddOption('--install_dir')
    AddOption('--install_ghost')
    AddOption('--home_dir')
    AddOption('--gantry')
    AddOption('--board')
    AddOption('--limit_detect')
    AddOption('--logging')
    AddOption('--binary')
    AddOption('--ubifs_settings')
    AddOption('--python33_dir')
    AddOption('--connman')
else:
    # make_current_link=True is necessary for header-only libraries on mac
    env.MBInstallHeaders(env.Glob('include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
    env.MBInstallHeaders(env.Glob('include/bwcoreutils/*'), 'bwcoreutils', make_current_link=True)
    env.MBCreateInstallTarget()
