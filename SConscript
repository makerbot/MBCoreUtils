
import os

env = Environment(ENV = os.environ, tools = ['default'])

command = os.path.join(str(Dir("#/")),  "birdwing/parse_enums.py") + ' -p -c -s'
print(command)

output_files = [
    'obj/machine_errors.hh',
    'obj/toolhead_errors.hh',
    'obj/all_errors.hh',
    'obj/machine_errors.py',
    'obj/toolhead_errors.py',
    ]
input_files = [
    'enum_parse.py',
    'parse_enums.py',
    'machine_errors.json',
    'toolhead_errors.json',
    ]

env.Command(output_files, input_files, command)
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "obj/machine_errors.hh")
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "obj/toolhead_errors.hh")
env.Install(os.path.join(str(Dir("#/")), 'include', 'bwcoreutils'), "obj/all_errors.hh")

path = os.path.join(str(Dir("#/")), 'include', 'bwcoreutils')
# This is here to prevent "cannot find target 'install'"  errors. 
# There may be a more logical thing to do with this alias 
Alias("install", path)

#
# This should only be done by MakerWare
#

mw_env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

# Add an empty command that makes the top-level directory target
# depend on the header files. This ensures the header files are copied
# into the variant dir.
mw_env.Command('.', mw_env.MBRecursiveFileGlob('include', '*.h'), '')

# make_current_link=True is necessary for header-only libraries on mac
mw_env.MBInstallHeaders(env.MBGlob('#/include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
mw_env.MBCreateInstallTarget()
