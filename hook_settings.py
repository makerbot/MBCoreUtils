
import hook_tools

hooks = [
    'pre-commit',
    'prepare-commit-msg'
]


def exclude_path(path, check):
    """Create a modified check that skips searching a specific path"""
    new_check = check.copy()
    new_check.match = [r'(?!^{path}/.*{match}$)(^.*{match}$)'.format(
        path=path, match=match) for match in new_check.match]
    return new_check

pre_commit_checks = [
    hook_tools.cpplint_check,
    hook_tools.pep8lint_check,
    hook_tools.jsonlint_check
]

pre_commit_checks = [exclude_path('birdwing_codegen/templates', chk)
                     for chk in pre_commit_checks]
