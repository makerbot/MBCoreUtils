import os

from SCons.Script import AddOption
from SCons.Node import NodeList

os.environ.setdefault('BWSCONSTOOLS_PATH', '#/../bw-scons-tools')

env = Environment(
    ENV=os.environ,
    tools=['default', 'mustache', 'birdwing_install',
           'birdwing_settingsgen', 'birdwing_build'],
    toolpath=['#/../mustache',
              '#/../bw-scons-tools'])

# MBRecursiveFileGlob is defined in both the mb_install tool, and the
# birdwing_install tool, and both implementations work slightly differently.
# We always want to use the one from mb_install, so grab it here before the
# birdwing_install tool is loaded.
_recursive_file_glob = env.MBRecursiveFileGlob

# -- Mustache-based codegen stuff -- #

BWCGEN_ROOT_DIR = 'birdwing_codegen'
BWCGEN_OUTPUT_DIR = 'birdwing'

machine = None

machine = GetOption('machine')


# We're building birdwing firmware for a specific machine, so have to
# do machine specific code-generation based off the
# printer_settings.json file for that machine.  Birdwing-Software gets
# built after MBCoreUtils, so we have to generate the right
# printer_settings.json file here too. This is so hacky but I don't see
# any less hacky way of doing it that doesn't require big refactors. :(
generated_settings = env.File("#/.build-" +
                              env.BWGetVariantDirSuffix() +
                              '/' + BWCGEN_OUTPUT_DIR + '/' +
                              'printer_settings.json')

env.BWGenSettings('printer_settings.json',
                  generated_settings)

# Declare the machine-specific settings file as an external source
# if we're doing codegen for a specific bot.  That way, templates will
# be re-rendered if the settings file changes.
external_sources = [generated_settings]

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

dynamic_context_args['MBCOREUTILS_BIRDWING'] = True

dynamic_context_args['BWMACHINE_SETTINGS'] = generated_settings

print("using dca " + str(dynamic_context_args))

templates_root = os.path.join(BWCGEN_ROOT_DIR, 'templates')
# I'm not sure that this file should be split up, but it does seem odd
# that it's shared by these three things
common_transformations_file = os.path.join(
    BWCGEN_ROOT_DIR, 'transformations.json')

outdir_base = 'obj/'+BWCGEN_OUTPUT_DIR

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

if env.BWShouldCrossBuild():
    env.Alias('install', shared_includes)
    env.BWInstall('/usr/settings', Glob('#/birdwing_codegen/static/*'))
# When our target is "install", we still need to build all
# local files.  These files are still required by install
# targets in other repositories.
Alias("install", 'include')
