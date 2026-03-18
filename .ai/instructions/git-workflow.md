# Git Workflow

## Branching Strategy

- Trunk-based development. Commit directly to `main`.

## Commits

- **Atomic commits**: do not exceed ~100 lines of change per commit.
- Commit messages must be concise and must not note what *didn't* change.
- Never amend commits or rewrite git history without an explicit request from the user. Only use `git commit --amend` or `git rebase` when specifically asked.

## Pre-commit Rule

**Before every commit, run the unit tests and `behave_stable_tests`. Only commit if all of them pass.**

See [testing.md](testing.md) for how to run the test suites.
