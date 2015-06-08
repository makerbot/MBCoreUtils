env = Environment(tools=['birdwing_install', 'birdwing_build'],
                  toolpath=['#/../bw-scons-tools'])

env.SConscript('SConscript',
               variant_dir='.build-'+env.BWGetVariantDirSuffix())
