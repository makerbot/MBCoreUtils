
try:
    import artifactory_utils
except:
    pass
else:
    dependencies = [
        artifactory_utils.ArtifactSelector(
            project="Toolchain-Release",
            revision="master",
            version="4.*",
            debug=False,
            stable_required=True),
        artifactory_utils.ArtifactSelector(
            project="mustache",
            revision="master",
            version="1.2.*",
            debug=False,
            stable_required=True)
    ]
