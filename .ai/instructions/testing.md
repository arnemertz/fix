# Testing

For how to invoke the test suites, see the [Running Tests section in BUILD.md](../../BUILD.md#running-tests).

This file covers agent-specific conventions for writing and organising tests.

## Development Workflow

### Feature level (BDD-first)
- After requirements and architecture are approved, the Tester writes Gherkin scenarios for the feature **before any implementation begins**.
- New scenarios are tagged `@wip`. They are expected to fail initially.
- The feature is considered done when all `@wip` scenarios pass and are promoted to stable.

### Commit level (TDD)
- The Tester and Coder work in tandem on each behavioral increment.
- The Tester writes unit tests for the next increment first; the Coder implements until they pass.
- Each commit contains both the production code and the unit tests covering it.
- See [git-workflow.md](git-workflow.md) for the full pre-commit rule.

## Unit Tests (Catch2 v2)

- Located under `test/`.
- Test file naming convention: `<module>_test.cpp`. If there is no clear primary unit under test, ask for guidance.
- A shared `catch_main` static library provides the Catch2 runner.
- `test/.clang-tidy` relaxes `readability-function-cognitive-complexity` for test files.
- **Test case names** must end with `"..."` if the test case contains sections.
- **Section names** must start with `"..."`.

## Integration Tests (behave)

- Located under `behave/`; feature files use Gherkin, step implementations are in `behave/steps/`.
- Scenarios tagged `@wip` are work-in-progress; scenarios tagged `@skip` are skipped.
