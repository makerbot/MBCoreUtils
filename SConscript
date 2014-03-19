import birdwing_code_gen
import os

env = Environment(ENV = os.environ, tools = ['default'])

env.Append(
    BUILDERS = {
        'birdwing_code_gen':
        Builder(action = birdwing_code_gen.gen_files)})

env.birdwing_code_gen(
    # Output files
    ['include/bwcoreutils/machine_errors.hh',
     'include/bwcoreutils/toolhead_errors.hh',
     'include/bwcoreutils/all_errors.hh',
     'birdwing/machine_errors.py',
     'birdwing/toolhead_errors.py'],

    # Input files
    ['birdwing/machine_errors.json',
     'birdwing/toolhead_errors.json',

     # Not used by the script, just for correct dependencies
     'site_scons/birdwing_code_gen.py'])

#
# This is my huge hack, sorry Ted
# TODO(pshaw): get Ted to help fix this
#
if ("MBCOREUTILS_BIRDWING" in os.environ):
    path = os.path.join(str(Dir("#/")), 'include', 'bwcoreutils')
    # This is here to prevent "cannot find target 'install'"  errors. 
    # There may be a more logical thing to do with this alias 
    Alias("install", path)
else:
    mw_env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

    # Add an empty command that makes the top-level directory target
    # depend on the header files. This ensures the header files are copied
    # into the variant dir.
    mw_env.Command('.', mw_env.MBRecursiveFileGlob('include', '*.h'), '')

    # make_current_link=True is necessary for header-only libraries on mac
    mw_env.MBInstallHeaders(mw_env.MBGlob('#/include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
    mw_env.MBInstallHeaders(mw_env.MBGlob('#/include/bwcoreutils/*'), 'bwcoreutils', make_current_link=True)
    mw_env.MBCreateInstallTarget()
