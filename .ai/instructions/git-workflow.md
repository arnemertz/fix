# Git Workflow

## Terminal Usage

- Always use `git --no-pager` for commands that may open a pager (e.g., `git --no-pager log`, `git --no-pager diff`, `git --no-pager show`).
- Never modify global git configuration (`git config --global`). All configuration changes must be scoped to the repository (`git config --local`) and require explicit user approval.

## Branching Strategy

- Feature branches off `main`. Branch naming: `feature/<short-description>` (e.g., `feature/add-priority-field`).
- The **Product Owner** creates the feature branch at the start of a task. Before branching, always check out `main` and pull from `origin` to ensure the branch starts from the latest state:
  ```
  git checkout main
  git pull origin main
  git checkout -b feature/<short-description>
  ```
- All agent work for a feature happens on that feature branch.
- PR target is always `main`.
- When the feature is complete and the Reviewer has signed off, the Product Owner notifies the user. *(Automated PR creation will be added later once repository workflows are set up.)*

## Commits

- **Atomic commits**: do not exceed ~100 lines of change per commit.
- Commit messages must be concise and must not note what *didn't* change.
- Never amend commits or rewrite git history without an explicit request from the user. Only use `git commit --amend` or `git rebase` when specifically asked.

## Pre-commit Rule

- ALL unit tests must pass before every commit — no exceptions.
- `behave_stable_tests` must also pass before every commit.
- Any commit that introduces new production code must include unit tests covering that new code.
- Pure refactoring commits are exempt from the "include new tests" requirement, but must still pass all existing tests.
- The Coder is encouraged to separate refactoring commits from behavioral increment commits to keep commits concise and satisfy these rules cleanly.
