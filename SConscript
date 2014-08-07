import mustache_based_codegen as mc
import machine_specific_settings_gen
import os
from SCons.Script import AddOption

env = Environment(ENV=os.environ, tools=['default', 'mb_install'])


### Mustache-based codegen stuff ###

AddOption('--bwsoftware',
          dest='bwsoftware',
          type='string',
          default=os.path.join(str(Dir("#/")), '../../', 'Birdwing-Software'),
          help='Set Birdwing-Software repo location'
               ' (if not ../../Birdwing-Software).')
AddOption('--machine', dest='machine')

BWCGEN_ROOT_DIR = 'birdwing_codegen'
BWCGEN_OUTPUT_DIR = 'birdwing'
bw_machine_settings_path = os.path.join(GetOption('bwsoftware'),
                                        'firmware',
                                        'settings')

env.Append(BUILDERS={
    'birdwing_code_gen': Builder(action=mc.gen_files),
    'generate_machine_settings': Builder(
        action=machine_specific_settings_gen.gen_machine_specific_settings)
})

try:
    machine = GetOption('machine')
except AttributeError:
    machine, machine_printer_settingsf = None, None
finally:
    if machine and os.path.exists(bw_machine_settings_path):
        # We're building birdwing firmware for a specific machine, so have to
        # do machine specific code-generation based off the
        # printer_settings.json file for that machine.  Birdwing-Software gets
        # built after MBCoreUtils, so we have to generate the right
        # printer_settings.json file here too. This is so hacky but I don't see
        # any less hacky way of doing it that doesn't require big refactors. :(
        machine_printer_settingsf = [
            f for f in os.listdir(bw_machine_settings_path) if
            f == 'printer_settings.json.{0}'.format(machine)
        ]
        if not machine_printer_settingsf:
            raise Exception('Unable to find printer_settings.json.{0}'
                            .format(machine))
        env.generate_machine_settings(
            os.path.join(BWCGEN_OUTPUT_DIR, 'printer_settings.json'),
            [
                os.path.join(bw_machine_settings_path,
                             'printer_settings.json'),
                os.path.join(bw_machine_settings_path,
                             machine_printer_settingsf[0])
            ]
        )
        env['MBCOREUTILS_BWMACHINE_SETTINGS'] = os.path.join(
            str(Dir("#/")),
            'obj',
            BWCGEN_OUTPUT_DIR,
            'printer_settings.json'
        )
    else:
        print('[WARNING] Mustache Codegen: Not building for a specific machine'
              ', codegen output will be missing machine-specific components.')


def valid_template_files(root_template_dir):
    """Yield valid template files given a root template dir"""
    lang_dirs = [os.path.join(root_template_dir, f) for f in
                 os.listdir(root_template_dir) if
                 os.path.isdir(os.path.join(root_template_dir, f))]

    for d in lang_dirs:
        for f in os.listdir(d):
            full_file_path = os.path.join(d, f)
            if os.path.isfile(full_file_path):
                yield full_file_path


def valid_context_files(root_context_dir):
    """Yield valid context files given a root context dir"""
    def valid_ext(f):
        return f.endswith('.json') or f.endswith('.py')

    for f in os.listdir(root_context_dir):
        full_path = os.path.join(root_context_dir, f)
        if os.path.isfile(full_path) and valid_ext(f):
            yield full_path

# Special file used to extend mustache's functionality, see docs.
transformations_full_path = os.path.join(BWCGEN_ROOT_DIR,
                                         mc.TRANSFORMATIONS_FILE)
# Script to process transformations & render templates.
codegen_builder_full_path = 'site_scons/mustache_based_codegen.py'
# Context json file(s) containing the data used to render templates.
bw_context_files = [c for c in valid_context_files(
    os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME))]
# Template files to be rendered.
bw_template_files = [t for t in valid_template_files(
    os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME))]

codegen_input_files = list(
    [transformations_full_path] +
    [codegen_builder_full_path] +
    bw_context_files +
    bw_template_files
)

# Append the machine-specific settings file to the input list if we're doing
# codegen for a specific bot.
if machine:
    codegen_input_files += [
        os.path.join(str(Dir("#/")),
                     'obj',
                     BWCGEN_OUTPUT_DIR,
                     'printer_settings.json')
    ]


def get_relpath(full_template_path):
    """Take a full path and return the <parentdir>/<filename>"""
    lang_dir = os.path.basename(os.path.dirname(full_template_path))
    name = os.path.basename(full_template_path)
    return os.path.join(lang_dir, name)

# these are the locations of the rendered templates.
# they will be saved to <variantdir>/birdwing/<lang>/<file>.
codegen_output_files = [os.path.join(BWCGEN_OUTPUT_DIR, get_relpath(path))
                        for path in bw_template_files]

# Do the code gen.
env.birdwing_code_gen(codegen_output_files, codegen_input_files)


def valid_shared_cpp_headers(file_list):
    """Yield valid cpp headers from a list of files"""
    def valid_ext(f):
        return f.endswith('.hh') or f.endswith('.h')

    def valid_dir(d):
        return os.path.basename(os.path.dirname(d)) == 'shared_cpp'

    for header in file_list:
        if valid_dir(header) and valid_ext(header):
            yield header

# Hack to copy codegen'd cpp files from obj/birdwing/cpp to
# obj/include/bwcoreutils. This is necessary since a bunch of projects already
# expect shared cpp birdwing headers to be there.
# TODO(jacksonh) - remove this awful hack
for header in valid_shared_cpp_headers(bw_template_files):
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
    env.MBInstallHeaders(env.Glob('include/mbcoreutils/*'),
                         'mbcoreutils', make_current_link=True)
    env.MBInstallHeaders(env.Glob('include/bwcoreutils/*'),
                         'bwcoreutils', make_current_link=True)
    env.MBCreateInstallTarget()
