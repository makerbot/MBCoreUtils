
import os

env = Environment(ENV = os.environ, tools = ['default', 'mb_install'])

env.MBInstallHeaders(env.MBGlob('#/cpp/include/mbcoreutils/*'), 'mbcoreutils')
env.MBCreateInstallTarget()