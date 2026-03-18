# Creating an Agentic Dev Team

**Date:** 2026-03-18

## Summary

Designed and created a portable AI agent team for the Fix project, consisting of six agents (Product Owner, Architect, Coder, Tester, Reviewer, Toolsmith) and five shared instruction files covering C++ code style, architecture, testing, git workflow, and build/dependencies. Along the way, several project improvements were made: east const enforcement added to `.clang-format`, `BUILD.md` updated with a Running Tests section and a C++23 fix, and `AGENTS.md` restructured to reference the new instruction files instead of duplicating content. The session covered both team design discussions and a file-by-file review and refinement pass.

---

## Conversation

---

**Human:** Read the Copilot online documentation and the Claude Code online documentation. I would like to create a dev team of agents for this project that is portable to other AI assistants. Propose a team constellation and create the agent files after we discuss and refine the number and kind of agents. Agent files should be created with file names and locations that are agnostic of the AI assistant, i.e. not specific to copilot or claude code. Ask me clarifying questions where needed, avoid far-fetched assumptions.

**Assistant:** After reading the existing project files (`AGENTS.md`, `.github/copilot-instructions.md`, directory structure), proposed an initial team of 3–4 agents:

| Agent | Focus |
|---|---|
| **Coder** | C++ implementation, project conventions |
| **Tester** | Catch2 unit tests, behave BDD tests |
| **Reviewer** | Code review, style, static analysis |
| **Build** *(optional)* | CMake, Conan, CI/CD |

Proposed `.ai/agents/` as the tool-agnostic file location.

Asked clarifying questions:
1. Agent count — 3 (without Build) or 4?
2. File location preference (`.ai/agents/`, `agents/`, `.agents/`, `docs/agents/`)?
3. Layering: shared `AGENTS.md` + per-agent files?
4. Blog/Docs agent needed?
5. Scope: role-specific rules only (referencing `AGENTS.md`) or fully self-contained?

---

**Human:** A build or infrastructure agent seems useful, at least in the beginning when we set up more tooling like sanitizers etc. I'd like to give the team tickets/issues to resolve on their own, should there be an agent for coordination and/or requirements engineering, e.g. a product owner?

`.ai/agents` looks good, might we also put specific instructions there, e.g. in `.ai/instructions/<topic>.md`? I am thinking about C++ code style, git workflow etc. as topics that might not be interesting for every single agent. That would also play into your 3rd and 5th question. I am no fan of duplicated content, I'd rather point them to `agents.md` and shared topic-specific instructions if that makes sense. I'll continue the blog manually, no agents needed for that.

**Assistant:** Revised proposal to 5 agents (Coder, Tester, Reviewer, Build, Product Owner). Proposed directory structure:

```
.ai/
├── agents/
│   ├── coder.md
│   ├── tester.md
│   ├── reviewer.md
│   ├── build.md
│   └── product-owner.md
└── instructions/
    ├── cpp-code-style.md
    ├── git-workflow.md
    ├── testing.md
    └── build-and-dependencies.md
```

Layering: `AGENTS.md` = single source of truth for project overview → instruction files = canonical topic content (replacing those sections in `AGENTS.md`) → agent files = role + references to instructions.

Asked:
1. Should `AGENTS.md` be restructured to reference instruction files, or stay self-contained?
2. PO scope: decompose only, or also orchestrate/delegate?
3. Any other instruction topics beyond the four listed?

---

**Human:** 1. Sounds very good. 2. The PO should take over the orchestration of the other agents and delegate work accordingly. Ideally, I would discuss a feature with the PO and it would clarify the requirements with me, and then the team goes through the implementation workflow on its own, presenting me with a pull request of the implemented feature. 3. Architecture would be a good topic. As you have seen in an initial analysis of the project, I strive for DDD-based architecture, separating the domain model from the CLI and possible other UI and persistence. We will refine those topics later when they emerge.

Speaking of architecture, should we have a dedicated architect, or is that something the product owner should cover? I would like to be involved in architecture decisions anyway, so the team will not be fully autonomous in that regard.

**Assistant:** Recommended a **dedicated Architect** (separate from PO) because:
- PO is already heavily loaded (requirements, orchestration, delegation)
- Architecture decisions are deeply technical (DDD, layer boundaries) vs. product decisions
- Architect operates proactively before/during implementation; Reviewer operates reactively after
- User involvement is cleaner with a dedicated collaborator for that dialog

Proposed workflow: User → PO (requirements) → Architect (design, presents to user for approval) → PO delegates to Coder/Tester/Build → Reviewer gates → PR to user.

Proposed final team of **6 agents**: Product Owner, Architect, Coder, Tester, Reviewer, Build. Also added `architecture.md` as a 5th instruction topic. Asked for go-ahead.

---

**Human:** Sounds lovely, go ahead!

**Assistant:** Created all files:

**`.ai/instructions/`** (5 files):
- `cpp-code-style.md` — east const, `[[nodiscard]]`, naming, error handling, formatting, construction patterns
- `architecture.md` — DDD layer rules, layer structure, key patterns, decision process
- `testing.md` — Catch2 conventions, behave conventions, running tests
- `git-workflow.md` — branching, commit rules, pre-commit checks
- `build-and-dependencies.md` — CMake, Conan, dependencies, static analysis, sanitizers

**`.ai/agents/`** (6 files): `product-owner.md`, `architect.md`, `coder.md`, `tester.md`, `reviewer.md`, `build.md`

**Updated:** `AGENTS.md` (restructured to lean overview with tables pointing to instruction/agent files), `.github/copilot-instructions.md` (updated to reference new structure).

---

**Human:** Please move the "Qualified names in Chat" section from the C++ style instructions to `copilot-instructions.md` as that was a Copilot specific issue and is not related to C++ programming in general.

**Assistant:** Moved the section from `.ai/instructions/cpp-code-style.md` to `.github/copilot-instructions.md`. The section describes a VS Copilot chat rendering quirk (`::`  inside inline backticks interpreted as search links), not a C++ style rule.

---

**Human:** Compare the root level `BUILD.md` with the new `build-and-dependencies.md` — the first should be kept as reference for humans getting started with the project, but the latter might contain duplicated information. We might want to reference `BUILD.md` in the AI instructions or remove the instructions altogether and point agents to the `BUILD.md` instead, depending on whether the AI instructions have useful information beyond `build.md`. What do you think?

**Assistant:** Compared both files:

- **Overlap:** basic build commands (CMake configure + build).
- **Unique to `build-and-dependencies.md`:** dependency table with exact Conan package versions, static analysis & sanitizers directives ("enable in CI", "don't add Doxygen blocks"), "Conan is invoked automatically" agent-specific note, test running command.
- **Unique to `BUILD.md`:** prerequisites list, detailed step-by-step Conan install, Visual Studio integration tips, toolchain file reference.
- **Also noticed:** `BUILD.md` says "C++20" — the project uses C++23.

Recommendation: keep both, slim down `build-and-dependencies.md` to agent-specific content only, reference `BUILD.md` for the general build procedure. Same pattern as later applied to `testing.md`.

---

**Human:** Make it so.

**Assistant:** Slimmed down `build-and-dependencies.md` to: Conan auto-invocation note, dependency table (Catch2, CLI11 with versions), static analysis & sanitizers section. Added reference to `BUILD.md` for general procedure. Fixed `BUILD.md`: C++20 → C++23.

---

**Human:** Let us refine the instructions and agents one by one. The git workflow should change; with the autonomous team of agents I would like to have pull requests, i.e. the team should work on feature branches instead of the main branch.

**Assistant:** Asked clarifying questions:
1. Branch naming convention?
2. PR target — always `main`?
3. Who creates the branch / opens the PR?
4. Force-push on feature branches allowed?

---

**Human:** Let's go with `feature/xyz`, PR target `main`. PO creating the feature branch is OK. Publishing the feature branch and creating the PR should become its responsibility later, I have yet to set up the repository correctly, for now let's keep work local. Instead of opening the PR, the PO should notify me that the feature is done, for now.

**Assistant:** Updated `git-workflow.md`: replaced trunk-based development with feature branch strategy (`feature/<short-description>` off `main`), PO creates the branch, notifies user on completion; PR creation to be added later. Updated `product-owner.md`: workflow now includes creating the feature branch (step 3) and ends with notifying the user.

---

**Human:** good. now let's talk C++ code style. The pointer alignment and column limit might be covered by `.clang-format` — can you verify that that is set up and covers those points? In that case, there should be no need to explicitly mention them.

**Assistant:** Read `.clang-format`. Both are explicitly set: `ColumnLimit: 120` and `PointerAlignment: Left`. Removed both from `.ai/instructions/cpp-code-style.md` — clang-format enforces them mechanically so repeating them in instructions adds no value.

---

**Human:** How about east const, is that covered by clang-format as well?

**Assistant:** No — clang-format does not enforce east/west const by default. There is a `QualifierAlignment` option (added in clang-format 14) that can enforce it, but the project's `.clang-format` doesn't set it. Offered to add `QualifierAlignment: Right` to have it enforced mechanically, which would allow removing it from the instructions too.

---

**Human:** yes, please.

**Assistant:** Checked installed clang-format version: 20.1.8 (well above the required 14). Added `QualifierAlignment: Right` to `.clang-format`. Removed east const rule from `.ai/instructions/cpp-code-style.md`.

---

**Human:** Do you know Jason Turner? Would "follow Jason Turner's best practices" be something an agent can work with? That would encompass nodiscard, constexpr by default, as well as a bunch of other rules.

**Assistant:** Yes — Jason Turner is a well-known C++ educator (C++ Weekly, CppCon talks, *C++ Best Practices* book/GitHub guide). Modern LLMs have good coverage of his principles.

Assessment:
- **Pros:** compact and meaningful signal; covers `[[nodiscard]]`, `constexpr` by default, avoiding globals, preferring value types, etc. without enumerating every rule.
- **Cons:** not a versioned spec; agent recollections may vary slightly; small risk of misattribution.

Recommendation: use as a *baseline reference* with project-specific rules taking precedence. Proposed wording: *"Follow Jason Turner's C++ best practices as a baseline. Project-specific rules below take precedence."*

---

**Human:** yes, put that reference first, it will allow us to skip the mention of nodiscard and constexpr for now, everything else can stay as it is.

**Assistant:** Added the Jason Turner baseline reference at the top of `cpp-code-style.md`. Removed `[[nodiscard]]` and `constexpr` items — both covered by the baseline.

---

**Human:** How full is your context?

**Assistant:** Qualitative assessment: moderately loaded (roughly a third to half of a typical context window). All files created in the session were in context. No risk of losing track of earlier decisions within the session; a new session would need to re-read files from disk.

---

**Human:** The last response seemed a bit slower than usual, but this one was fine.

**Assistant:** Acknowledged. Noted user is already on branch `copilot_playground`. Offered to continue with next file.

---

**Human:** let me quickly close the file we covered and move on to the remaining ones.

**Assistant:** Listed remaining files: 2 instruction files (`testing.md`, `architecture.md`) and 5 agent files (`architect.md`, `coder.md`, `tester.md`, `reviewer.md`, `build.md`). Suggested doing instruction files first since agents reference them.

---

**Human:** architecture.md looks good. testing.md has details on how to invoke tests — that either might be duplicated information (e.g. from the `behave/CMakeLists.txt`) or is information that is also interesting for humans and should be extracted to a location that is not in the `.ai` instructions, maybe top level `BUILD.md`?

**Assistant:** Compared `testing.md`, `BUILD.md`, and `behave/CMakeLists.txt`. Found:

- **Invocation commands** (`ctest`, `behave -t ~skip -t ~wip`, etc.): the behave commands are already in `behave/CMakeLists.txt`; neither the CTest nor behave commands are in `BUILD.md` (which currently ends at "build as normal" with no testing section at all). Useful for humans → belong in `BUILD.md`.
- **Agent-specific conventions** (no duplication anywhere): `<module>_test.cpp` naming, `catch_main` library structure, clang-tidy relaxation for test files, test case/section naming (`"..."` rules), `@wip`/`@skip` tag semantics.

Recommendation: add "Running Tests" section to `BUILD.md`, strip invocation commands from `testing.md`, have it reference `BUILD.md`. Agent conventions stay in `testing.md`.

---

**Human:** yes, please.

**Assistant:** Added Running Tests section to `BUILD.md` (CTest and direct behave invocations). Stripped invocation commands from `testing.md`, replaced with reference to `BUILD.md`. `testing.md` now contains only agent-specific conventions.

---

**Human:** looks good. that covers the instructions, I think.

**Assistant:** Confirmed all 5 instruction files reviewed and complete. Moved on to agent files. `product-owner.md` already covered during git workflow discussion. Remaining: `architect.md`, `coder.md`, `tester.md`, `reviewer.md`, `build.md`.

---

**Human:** we did some changes to the product owner when going over the instructions, but I have not fully reviewed it yet. I'll want to do that last, as it ties everything together.

**Assistant:** Noted. Proceeded with `architect.md` first.

---

**Human:** architect looks solid. Next in line: tester.

**Assistant:** Read `tester.md`. Found one issue: the Rules section still mentioned "east const" explicitly — stale after east const was moved to clang-format enforcement. Flagged for cleanup.

---

**Human:** Let's talk development workflow. I'd like to go for actual BDD, i.e. when the requirements and architecture decisions for a feature are clear, write Gherkin scenarios first, then step implementations. Scenarios will fail at first and should remain WIP until they pass. A feature is done when all defined BDD tests pass. For individual commits, there should be no code that is not unit tested, i.e. the tester and coder should work in tandem to write a code increment including the unit tests that cover it. Does that sound reasonable?

**Assistant:** Confirmed this is a classic outside-in BDD + inner-loop TDD approach. Summarised understanding:

- **Feature level (BDD-first):** Tester writes Gherkin scenarios → tagged `@wip` → implementation proceeds until all pass → feature done.
- **Commit level (TDD):** Tester writes unit tests first, Coder implements until they pass, each commit = code + tests.
- Noted that `behave_stable_tests` already excludes `@wip` by tag, so failing WIP scenarios don't block commits.

Identified files to update: `testing.md`, `tester.md`, `coder.md`, `product-owner.md`, `git-workflow.md`. Asked for confirmation before proceeding.

---

**Human:** git-workflow: the commit must include tests for any new code (does not apply to pure refactoring commits), but it must pass ALL unit tests, not only the new ones, no excuses. Coder is encouraged to separate refactorings from behavioral increments to satisfy the rule for concise commits.

**Assistant:** Updated 5 files in one operation:

- **`git-workflow.md`:** Pre-commit rule now has four explicit bullets: all unit tests pass (no exceptions), `behave_stable_tests` passes, new code requires accompanying tests, pure refactoring commits exempt from new tests but not from passing all existing ones. Added separation encouragement.
- **`testing.md`:** Added "Development Workflow" section: BDD-first (feature level) and TDD (commit level).
- **`tester.md`:** Workflow split into Phase 1 (BDD scenarios before implementation) and Phase 2 (TDD support per increment). Cleaned up stale "east const" mention.
- **`coder.md`:** Workflow now starts from receiving an increment with tests already written. Rules gained explicit separation of refactoring vs. behavioral commits. Removed stale style details.
- **`product-owner.md`:** Responsibilities and Workflow updated — BDD scenarios before implementation, increments delegated as Tester→Coder pairs, done condition is `@wip` scenarios passing.

---

**Human:** great. I think we can continue with the review of the agents.

**Assistant:** Moved to `reviewer.md`.

---

**Human:** [reviewing reviewer.md] 1. "clang-format clean" should do for the checklist items east const/nodiscard/constexpr — I would remove nodiscard and constexpr in favour of "adheres to cpp-code-style.md" which covers those two via the Jason Turner reference. 2. Per-increment reviews sound better, so we get fast feedback and corrections.

**Assistant:** Updated `reviewer.md`: checklist now has "clang-format reports no changes" + "adheres to cpp-code-style.md" instead of individual items; workflow is now per-increment with a final light pass over the full branch at the end. Updated `product-owner.md`: step 8 requests Reviewer sign-off per increment (before commit), with blocker/re-review loop; step 9 keeps final pass before delivery.

---

**Human:** I like the "final light pass" for the reviewer. Any warnings and suggestions that are not fixed directly should be passed along to the user by the PO, so the user can decide to request a polishing commit.

**Assistant:** Updated `reviewer.md`: final pass now explicitly collects warnings/suggestions and forwards them to the PO. Updated `product-owner.md`: delivery notification now includes any outstanding warnings/suggestions from the final Reviewer pass.

---

**Human:** yes. First finding: the naming is not consistent with "reviewer", "architect", etc — those are roles a person would have. "build" is not. Also it is easily confused with the root level "BUILD.md". Is there a better name for that role?

For the content: Changes to the dependencies, tooling, etc. that go beyond adding source files or library targets to a CMakeLists.txt should be signed off by the user before development builds on those changes.

**Assistant:** Proposed naming candidates:

| Name | Notes |
|---|---|
| `devops` | Widely understood, but broad — often implies cloud/ops too |
| `toolsmith` | Specific and evocative, informal but fitting for a C++ learning project |
| `platform-engineer` | Modern and accurate, but hyphenated |

Recommended **`toolsmith`** as distinct and unambiguous.

Confirmed the user sign-off rule for non-trivial changes (similar to Architect's gate): trivial = adding source files/library targets to existing CMakeLists.txt; everything else requires user approval before proceeding.

---

**Human:** toolsmith sounds great, go for it.

**Assistant:** Created `toolsmith.md` with updated role, renamed workflow to distinguish trivial vs. non-trivial changes with user approval gate for the latter. Removed `build.md`. Updated references in `AGENTS.md` and `product-owner.md`.

---

**Human:** yes [to reviewing product-owner.md]. What I see in the workflow section: "Consult the Architect for design (if the feature involves structural changes)." Who decides whether the feature involves structural changes — the PO or the architect? Or does the user have to make that explicit during the requirements discussion?

**Assistant:** Presented four options:

1. User decides — adds burden, assumes user always knows upfront.
2. PO decides — PO is not a technical role, weak judge of architectural impact.
3. Always consult — safe but wasteful for trivial changes.
4. PO applies heuristic, defaults to consulting — PO skips only when demonstrably self-contained; Architect can also declare "nothing structural here".

Recommended **option 4**.

---

**Human:** Option 4 sounds good.

**Assistant:** Updated `product-owner.md`: step 4 now uses the default-consult heuristic with explicit criteria (no new types, no new files, no layer interactions touched). Also fixed a duplicate step 8 that had crept in from an earlier edit. Workflow now cleanly numbered 1–10 with per-increment loop as sub-steps.

---

**Human:** product owner looks good to me. Please go a final round over agents and instructions to verify that nothing is in the wrong place and we have no duplicate info.

**Assistant:** Read all 11 files. Found 5 issues:

1. **`git-workflow.md`** — trailing line redirected to `testing.md` for running tests, but `testing.md` itself redirects to `BUILD.md` (indirect chain). Removed.
2. **`product-owner.md` Responsibilities #3** — still used old "if it affects structure" phrasing, inconsistent with the "default-consult" heuristic in Workflow step 4. Aligned.
3. **`product-owner.md` References** — missing `git-workflow.md` even though Rules link to it. Added.
4. **`reviewer.md` Responsibilities** — said "review all changed files" implying the whole branch, while workflow correctly said per-increment. Fixed.
5. **`architect.md`** — the only agent without a Workflow section. Added (assess → propose → present to user → guide Coder).

---

**Human:** Thanks for the fixes, we should commit that now.

**Assistant:** Ran tests (all 19 passed: 17 unit tests + `behave_stable_tests`). Committed in three logical commits:

1. `Enforce east const via QualifierAlignment in clang-format`
2. `Update BUILD.md: fix C++23, add Running Tests section`
3. `Add AI agent team: agents, instructions, and restructured AGENTS.md`

All on branch `copilot_playground`.

---
