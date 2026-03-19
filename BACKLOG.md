# Fix — Backlog

Future stories and enhancements identified during development.

---

## Issue Management

### `.fix/` Directory Discovery and Creation
- Walk up directory tree looking for `.fix/` when Fix is invoked
- Prompt user to create `.fix/` if not found
- Rationale: Git-agnostic operation; allows Fix to work in any directory structure

### Editable Issue Title and Description
- Allow editing title/description while preserving the original issue ID
- Rationale: The ID acts as a permanent identifier; content should be mutable

### Issue Status Management
- Store status field in TOML (`open`, `closed`, `in-progress`, etc.)
- Commands to transition status
- Update listing output to reflect status changes

### Hash Collision Handling (Low Priority)
- Current design: 7-digit truncated SHA from title + description
- Collision probability is low; currently out of scope
- Future consideration: If two different issues produce the same ID, detect and handle gracefully (e.g., append disambiguator, or warn user)

---

## Meta

This file is maintained by the Product Owner agent during requirements clarification and design discussions.
