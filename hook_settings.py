
import hook_tools

hooks = [
    'pre-commit',
    'prepare-commit-msg'
]

pre_commit_checks = [
    hook_tools.cpplint_check,
    hook_tools.pep8lint_check,
    hook_tools.jsonlint_check
]

for check in pre_commit_checks:
    check.ignore.append('birdwing_codegen/templates/*')
