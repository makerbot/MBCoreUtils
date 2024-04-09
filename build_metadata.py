
try:
    import artifactory_utils
except:
    pass
else:
    dependencies = [
        artifactory_utils.ArtifactSelector(
            project="Toolchain-Release",
            revision="ReleaseMorepork2.2",
            version="^4.6",
            debug=False,
            stable_required=True),
        artifactory_utils.ArtifactSelector(
            project="mustache",
            revision="ReleaseMorepork2.2",
            version="^1.2",
            debug=False,
            stable_required=True)
    ]
