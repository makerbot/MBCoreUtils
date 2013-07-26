
import os

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

env.MBInstallHeaders(env.MBGlob('#/cpp/include/mbcoreutils/*'), 'mbcoreutils', make_current_link=True)
env.MBCreateInstallTarget()