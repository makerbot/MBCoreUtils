
try:
    import artifactory_utils
except:
    pass
else:
    dependencies = [
        artifactory_utils.ArtifactSelector(
            project="Toolchain-Release",
            revision="develop",
            version="^4.6",
            debug=False,
            stable_required=True),
        artifactory_utils.ArtifactSelector(
            project="mustache",
            revision="develop",
            version="^1.2",
            debug=False,
            stable_required=True)
    ]
