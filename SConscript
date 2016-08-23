import os
import zipfile
from SCons.Script import AddOption
from SCons.Node import NodeList
import SCons.Util

os.environ.setdefault('BWSCONSTOOLS_PATH', '#/../bw-scons-tools')

env = Environment(
    ENV=os.environ,
    tools=['default', 'mustache', 'birdwing_install',
           'birdwing_settingsgen', 'birdwing_build'],
    toolpath=['#/../mustache/scons',
              '#/../bw-scons-tools'])

# MBRecursiveFileGlob is defined in both the mb_install tool, and the
# birdwing_install tool, and both implementations work slightly differently.
# We always want to use the one from mb_install, so grab it here before the
# birdwing_install tool is loaded.
_recursive_file_glob = env.MBRecursiveFileGlob

# -- Mustache-based codegen stuff -- #

BWCGEN_ROOT_DIR = 'birdwing_codegen'
BWCGEN_OUTPUT_DIR = 'birdwing'

# Used in multiple places so might as well define it here
templates_dir = os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, 'templates')

dynamic_context_args = {'MBCOREUTILS_BIRDWING': True}

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
    dynamic_context_args=dynamic_context_args)
shared_cpp = env.MustacheCodegen(
    contexts=bwcodegen_contexts,
    templates=env.Glob(os.path.join(templates_root, 'shared_cpp', '*')),
    out_dir=os.path.join(outdir_base, 'shared_cpp'),
    transformations_file=common_transformations_file,
    dynamic_context_args=dynamic_context_args)
python_files = env.MustacheCodegen(
    contexts=bwcodegen_contexts,
    templates=env.Glob(os.path.join(templates_root, 'python', '*')),
    out_dir=os.path.join(outdir_base, 'python'),
    transformations_file=common_transformations_file,
    dynamic_context_args=dynamic_context_args)

env.Alias('install', [machine_cpp, shared_cpp, python_files])

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

# Install all of our python files as an "mbcoreutils" python package
for py_file in python_files:
    env.BWPyInstallPkg(str(py_file), subpkg='mbcoreutils')


def build_translation_zip(env, target, source):
    if SCons.Util.is_List(target):
        target = target[0]
    if not SCons.Util.is_List(source):
        source = [source]
    with zipfile.ZipFile(str(target), 'w') as myzip:
        for s in source:
            myzip.write(str(s), os.path.basename(str(s)))

if env.BWShouldDevBuild():
    env.BWDependsOnQt()
    env.BWDependsOnQt()
    languages = ['de', 'es', 'fr', 'ja', 'kr', 'zh', 'it', 'pr', 'es_la']
    translation_targets = map(lambda l: 'errors_'+l+'.ts', languages)
    translation_target_dir = 'src'
    translation_target_orig_dir\
        = '#/translations'
    translation_files = map(lambda l: translation_target_orig_dir+'/'+l,
                            translation_targets)
    update = env.Ts4(translation_files,
                     shared_cpp)
    env.Precious(translation_files)
    env.Alias('translations', update)
    translation_zip = env.Command('error_translations.zip',
                                  translation_files,
                                  build_translation_zip)
    env.Alias('translations', translation_zip)

# When our target is "install", we still need to build all
# local files.  These files are still required by install
# targets in other repositories.
Alias("install", 'include')
