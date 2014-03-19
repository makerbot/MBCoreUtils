
import os

env = Environment(ENV = os.environ, tools = ['default'])

command = os.path.join(str(Dir("#/")),  "birdwing/parse_enums.py") + ' -s'
print(command)

output_files = [
    'birdwing/obj/machine_errors.hh',
    'birdwing/obj/toolhead_errors.hh',
    'birdwing/obj/all_errors.hh',
    'birdwing/obj/machine_errors.py',
    'birdwing/obj/toolhead_errors.py',
    ]
input_files = [
    'birdwing/parse_enums.py',
    'birdwing/machine_errors.json',
    'birdwing/toolhead_errors.json',
    ]

env.Command(output_files, input_files, command)
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "birdwing/obj/machine_errors.hh")
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "birdwing/obj/toolhead_errors.hh")
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "birdwing/obj/all_errors.hh")
    
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
