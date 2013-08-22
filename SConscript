
import os

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

# make_current_link=True is necessary for header-only libraries on mac
env.MBInstallHeaders(env.MBGlob('#/cpp/include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
env.MBCreateInstallTarget()
