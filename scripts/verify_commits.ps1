param(
    [string]$BuildDir = "build",
    [string]$BaseBranch = "main"
)

# Save current branch so we can return to it at the end
$currentBranch = git --no-pager branch --show-current

# Get commits oldest-first
$commits = git --no-pager log --oneline "${BaseBranch}..HEAD" --reverse |
    ForEach-Object { $_.Split(" ")[0] }
$total = $commits.Count
$failed = @()
$firstCommit = $true

Write-Host "Verifying $total commits from '${BaseBranch}..HEAD' (will return to '$currentBranch')...`n"

foreach ($sha in $commits) {
    $msg = git --no-pager log --oneline -1 $sha
    Write-Host "=== $msg ==="

    git checkout $sha --quiet 2>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  CHECKOUT FAILED"
        $failed += "$sha (checkout)"
        continue
    }

    # Reconfigure so VS project files reflect this commit's CMakeLists.txt
    cmake -B $BuildDir | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  CMAKE CONFIGURE FAILED"
        $failed += "$sha (configure)"
        continue
    }

    # First commit: clean-first to flush any stale .obj/.pdb from previous runs.
    # Subsequent commits: incremental — going forward in time is safe.
    $cleanFlag = if ($firstCommit) { "--clean-first" } else { "" }
    $firstCommit = $false
    cmake --build $BuildDir --config Debug $cleanFlag
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  BUILD FAILED"
        $failed += "$sha (build)"
        continue
    }

    # Unit tests — exclude behave ctest targets
    ctest --test-dir $BuildDir -C Debug -E "behave" --output-on-failure
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  UNIT TESTS FAILED"
        $failed += "$sha (unit)"
        continue
    }

    # Stable behave tests via ctest (WORKING_DIRECTORY = behave/ as configured)
    ctest --test-dir $BuildDir -C Debug -R "behave_stable" --output-on-failure
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  STABLE BEHAVE TESTS FAILED"
        $failed += "$sha (behave)"
        continue
    }

    Write-Host "  OK`n"
}

# Restore original branch
git checkout $currentBranch --quiet 2>&1 | Out-Null
Write-Host ""

if ($failed.Count -eq 0) {
    Write-Host "All $total commits passed."
} else {
    Write-Host "FAILURES:"
    $failed | ForEach-Object { Write-Host "  $_" }
    exit 1
}
