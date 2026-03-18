# Testing

## Unit Tests (Catch2 v2)

- Located under `test/`.
- Test file naming convention: `<module>_test.cpp`. If there is no clear primary unit under test, ask for guidance.
- A shared `catch_main` static library provides the Catch2 runner.
- `test/.clang-tidy` relaxes `readability-function-cognitive-complexity` for test files.
- **Test case names** must end with `"..."` if the test case contains sections.
- **Section names** must start with `"..."`.
- Run via CTest:
  ```powershell
  ctest --test-dir <build_dir> --output-on-failure
  ```

## Integration Tests (behave)

- Located under `behave/`; feature files use Gherkin, step implementations are in `behave/steps/`.
- Scenarios tagged `@wip` are work-in-progress; scenarios tagged `@skip` are skipped.
- Run **stable** tests (excludes `@wip` and `@skip`):
  ```powershell
  behave -t ~skip -t ~wip
  ```
- Run **WIP** tests only:
  ```powershell
  behave -t wip --no-capture --no-logcapture
  ```
- Both are registered as CTest targets (`behave_stable_tests`, `behave_wip_tests`) in `behave/CMakeLists.txt`.
