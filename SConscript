
import os

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

# Add an empty command that makes the top-level directory target
# depend on the header files. This ensures the header files are copied
# into the variant dir.
env.Command('.', env.MBRecursiveFileGlob('include', '*.h'), '')

# make_current_link=True is necessary for header-only libraries on mac
env.MBInstallHeaders(env.MBGlob('#/include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
env.MBCreateInstallTarget()
