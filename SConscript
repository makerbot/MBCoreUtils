import mustache_based_codegen as mc
import os
from SCons.Script import AddOption

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])


# Mustache-based codegen stuff
BWCGEN_ROOT_DIR = 'birdwing_codegen'

env.Append(BUILDERS = {
    'birdwing_code_gen': Builder(action = mc.gen_files)
    })


# List of template relative location strings, in the format <parent dir>/<filename>.
# This is done this way b/c parent dir has special meaning for codegen, see docs for more info.
# Used to construct both codegen source and target dicts.
os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME)
bw_template_files = [os.path.join(d, f) for d in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME))
                                        if os.path.isdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d))
                                        for f in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d))
                                        if os.path.isfile(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, d, f))]

env.birdwing_code_gen(
    ## Output Files ##
    # these are the rendered templates - saved to <variantdir>/birdwing/<lang>/<file>
    map(lambda relpath: os.path.join('birdwing', relpath), bw_template_files),

    ## Input Files ##
    # Special file used to extend mustache's functionality. See docs.
    [os.path.join(BWCGEN_ROOT_DIR, mc.TRANSFORMATIONS_FILE),
    # Script to process transformations file & render templates.
    'site_scons/mustache_based_codegen.py'] +
    # Context dictionary(s) containing the data used to render templates.
    [os.path.join(BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME, f) for f in os.listdir(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME))
                                         if os.path.isfile(os.path.join(str(Dir("#/")), BWCGEN_ROOT_DIR, mc.CONTEXT_DIR_NAME, f)) and f.endswith('.json')] +
    # Template files to be rendered.
    map(lambda relpath: os.path.join(BWCGEN_ROOT_DIR, mc.TEMPLATES_DIR_NAME, relpath), bw_template_files)
)

# TODO(jacksonh) -- add in a hack to copy the genn'd cpp files to the include dir in the variantdir
#output_headers = [
#    'include/bwcoreutils/machine_errors.hh',
#    'include/bwcoreutils/toolhead_errors.hh',
#    'include/bwcoreutils/all_errors.hh'
#]


# Add an empty command that makes the top-level directory target
# depend on the header files. This ensures the header files are copied
# into the variant dir.
env.Command(
    '.',
    env.MBRecursiveFileGlob('include', '*.h') +
    ['include/bwcoreutils/bot_error.hh'],
    '')


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
    AddOption('--machine')
    AddOption('--ubifs_settings')
    AddOption('--python33_dir')
    AddOption('--connman')
else:
    # make_current_link=True is necessary for header-only libraries on mac
    env.MBInstallHeaders(env.Glob('include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
    env.MBInstallHeaders(env.Glob('include/bwcoreutils/*'), 'bwcoreutils', make_current_link=True)
    env.MBCreateInstallTarget()
