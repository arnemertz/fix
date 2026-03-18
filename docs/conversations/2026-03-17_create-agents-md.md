# Creating AGENTS.md

**Date:** 2026-03-17

## Summary

Bootstrapped `AGENTS.md` as the single source of truth for AI agent instructions in the Fix project. The assistant explored the full project structure (CMake/Conan setup, source namespaces, Catch2 tests, behave integration tests, clang-format/-tidy config, git log) and produced an initial `AGENTS.md`. Ten clarifying questions were asked about conventions not apparent from code; the answers were incorporated in a second pass. Finally, content that Copilot's memory system had injected back into `.github/copilot-instructions.md` was moved to `AGENTS.md`, and a meta-rule was added directing agents to always extend `AGENTS.md` rather than `copilot-instructions.md` for new instructions.

---

## Conversation

---

**Human:** Create an `AGENTS.md` in the project root and populate it with relevant information about the project. Ask me questions about preferences regarding coding style, git workflow, and others that are not apparent from the project itself. If possible, refer to previous conversations to learn details. Also move the content of the project-specific `copilot-instructions.md` to the new `AGENTS.md`.

**Assistant:** Explored the project by reading:
- `CMakeLists.txt` (CMake/Conan setup, C++23, optional testing flag)
- `README.md` (lightweight issue tracker, learning project, blog at arne-mertz.de)
- `.github/copilot-instructions.md` (pre-commit test rule)
- `.github/agents/Jason.agent.md` and `Jason_Reviewer.agent.md`
- `conanfile.txt` (Catch2 v2.13.10, CLI11 v2.3.2)
- `src/` structure: `fix::cli` (CLI layer) and `fix::domain` (domain model)
- `test/` structure: Catch2 unit tests, shared `catch_main`
- `behave/` structure: feature files + Python steps
- `.clang-format` (LLVM base, 120-col, pointer-left)
- `.clang-tidy` (most checks enabled)
- `src/domain/title.hpp`, `domain_error.hpp`, `application_service.hpp` (domain patterns: `std::expected`, `create()` factory)
- Recent git log

Created `AGENTS.md` with sections: Project Overview, Repository Structure, Tech Stack, Code Style, Naming Conventions, Testing (Catch2 + behave), Pre-commit rule, Git Workflow, Build & Dependencies, C++ Qualified Names in Chat.

Moved the pre-commit rule from `.github/copilot-instructions.md` into `AGENTS.md` and replaced it with a single reference line pointing to `AGENTS.md`.

Asked the following questions about things not apparent from the project:

1. **Branching strategy** — feature branches or trunk-based? Branch naming conventions?
2. **Commit granularity** — atomic or squash before merge?
3. **Member variable naming** — prefix/suffix (`m_`, `_`) or plain `snake_case`?
4. **`[[nodiscard]]`** — broadly or selectively?
5. **`constexpr` / `consteval`** — everywhere possible or only where compile-time use is explicit?
6. **New domain classes** — always `create()` factory, or direct construction acceptable?
7. **Test file naming** — is `<module>_test.cpp` fixed, or are other suffixes acceptable?
8. **behave stable tests command** — specific invocation to document?
9. **Doxygen** — actively maintained or scaffolding only?
10. **Sanitizers / static analysis in CI** — running anywhere, or local only?

---

**Human:** 
1. Trunk-based, the `copilot_playground` branch is only for exploration  
2. Atomic commits, do not exceed 100 LOC  
3. Plain `snake_case` for members  
4. `[[nodiscard]]` by default  
5. Make functions `constexpr` where possible  
6. Direct construction is acceptable in general if no checks have to be performed during construction, `create()` function returning `expected<T>` otherwise  
7. `<module>_test.cpp` is the convention; if there is no clear primary unit under test, ask for guidance  
8. The command is documented via `behave/CMakeLists.txt`  
9. Doxygen is not actively used  
10. I don't, but I should

**Assistant:** Read `behave/CMakeLists.txt` to get the exact invocation:
- Stable tests: `behave -t ~skip -t ~wip` (CTest target: `behave_stable_tests`)
- WIP tests: `behave -t wip --no-capture --no-logcapture` (CTest target: `behave_wip_tests`)

Updated `AGENTS.md` with all ten answers:

- **Code Style section** expanded with `[[nodiscard]]` by default, `constexpr` wherever possible, plain `snake_case` members, and the direct-construction vs. `create()` factory rule.
- **Testing section** expanded with `<module>_test.cpp` convention and a note to ask for guidance if no clear primary unit; exact behave commands and CTest target names documented.
- **Git Workflow section** updated with trunk-based development and the ≤100 LOC atomic commit rule.
- **New section "Static Analysis & Sanitizers"** added: clang-tidy config described, ASAN/UBSAN noted as not yet in CI but should be, Doxygen marked as scaffolded only (no Doxygen comment blocks).

---

**Human:** Please move the new contents of the `copilot-instructions.md` to `AGENTS.md` and note to always extend `AGENTS.md` for new memory instructions unless the instructions are specific to GitHub Copilot.

**Assistant:** Read `.github/copilot-instructions.md` and found it had been repopulated by Copilot's memory system with content already present in `AGENTS.md` (general guidelines, code style, testing/QA bullet points).

- Stripped `.github/copilot-instructions.md` back to a single reference line pointing to `AGENTS.md`.
- Added a prominent note at the top of `AGENTS.md`:
  > **For AI agents:** This is the single source of truth for project guidelines, coding conventions, and workflow rules. Always extend *this file* when recording new preferences or instructions. Only add content to `.github/copilot-instructions.md` if it is specific to GitHub Copilot and has no relevance to other agents.
