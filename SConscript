import birdwing_code_gen
import os
from SCons.Script import AddOption

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

env.Append(
    BUILDERS = {
        'birdwing_code_gen':
        Builder(action = birdwing_code_gen.gen_files)})

# Note: the order of these headers matters in birdwing_code_gen.py
output_headers = [
    'include/bwcoreutils/machine_errors.hh',
    'include/bwcoreutils/toolhead_errors.hh',
    'include/bwcoreutils/all_errors.hh'
]

env.birdwing_code_gen(
    # Output files
    output_headers +
    ['birdwing/machine_errors.py',
     'birdwing/toolhead_errors.py'],

    # Input files
    ['birdwing/machine_errors.json',
     'birdwing/toolhead_errors.json',

     # Not used by the script, just for correct dependencies
     'site_scons/birdwing_code_gen.py'])


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
