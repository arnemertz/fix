# Domain Model

This document describes the domain entities, value objects, and business rules for the Fix issue tracker.

---

## Entities

### `issue`

The `issue` entity is the aggregate root for an issue in Fix. It encapsulates the issue's identity, title, and description.

**Properties**:
- `issue_id`: Unique identifier (value object)
- `title`: Issue title (value object)
- `description`: Issue description (value object)
- Status: Hardcoded to `"open"` for now; will be added as a mutable property in a future story

**Creation**: Use the `issue::create()` factory method, which validates title and description and generates the issue ID.

**Invariants**:
- Title must not be empty (minimum one word after trimming)
- Description must not be empty after trimming
- Issue ID is immutable once created

---

## Value Objects

### `issue_id`

**Format**: `<prefix>-<hash>`

Where:
- `<prefix>`: Derived from the first 1–4 words of the title (see Prefix Generation below)
- `<hash>`: 7-digit hexadecimal hash of the title + description (see Hash Generation below)

**Example**: `"Fix the bug in parser"` with description `"Parser crashes on empty input"` → `fix-the-bug-in-a1b2c3d`

#### Prefix Generation

1. Trim leading/trailing whitespace from title
2. Split title into words by spaces
3. Take the first 4 words (or fewer if title has < 4 words)
4. For each word, take the first 3 characters and convert to lowercase
5. Join with hyphens (`-`)
6. Pad with placeholder segments if needed:
   - 1 word: `wor-xxx-yyy-zzz`
   - 2 words: `wor-sec-yyy-zzz`
   - 3 words: `wor-sec-thi-zzz`
   - 4+ words: `wor-sec-thi-fou` (no padding)

**Rationale**: The prefix provides human-readable context at a glance. Padding ensures consistent ID structure.

#### Hash Generation

1. Trim leading/trailing whitespace from title and description
2. Concatenate: `<trimmed_title> + <trimmed_description>` (no separator)
3. Compute `std::hash<std::string>` of the concatenated string
4. Truncate to 7 hexadecimal digits (mask: `hash & 0xFFFFFFF`)

**Rationale**: The hash disambiguates issues with the same or similar titles. 7 hex digits (28 bits) provide ~268 million unique values, sufficient for typical project sizes. Collisions are theoretically possible but out of scope for now.

**Note**: Since the hash is derived from title + description, two issues with identical title and description will have the same ID. This is used for duplicate detection (see Duplicate Issues below).

---

### `title`

**Validation**:
- Must not be empty after trimming leading/trailing whitespace
- Must contain at least one word (whitespace-separated)

**Error**: Returns `domain_error_code::empty_title` if validation fails.

---

### `description`

**Validation**:
- Must not be empty after trimming leading/trailing whitespace

**Error**: Returns `domain_error_code::empty_description` if validation fails.

---

## Business Rules

### Duplicate Issues

Two issues are considered duplicates if they have the same title and description (after trimming). This results in the same `issue_id`.

**Behavior**: Attempting to create an issue with the same ID as an existing issue returns `domain_error_code::issue_already_exists`.

**Future consideration**: When title/description editing is added, the ID will remain fixed. At that point, two issues with the same ID could represent either:
- A hash collision (extremely rare)
- Issues that had identical title+description at creation time

Distinguishing these cases is out of scope.

---

### Validation Error Reporting

When creating an issue, all validation errors are collected and reported together (not fail-fast). Errors are reported in this order:
1. Title validation errors
2. Description validation errors

**Rationale**: Allows users to fix all issues at once rather than iterating one error at a time.

---

## Repository Contract

The `issue_repository` interface defines how issues are persisted:

- `save(issue const&)`: Persists an issue (idempotent; overwrites if ID exists)
- `find_all()`: Returns all issues, sorted alphabetically by issue ID
- `exists(issue_id const&)`: Checks if an issue with the given ID exists

**Implementation note**: The concrete TOML implementation stores issues in `.fix/issues/<issue-id>.toml`.

---

## Future Stories

See [BACKLOG.md](../../BACKLOG.md) for planned enhancements:
- Editable title/description (ID stays fixed)
- Status field (open/closed/in-progress)
- `.fix/` directory discovery and creation
