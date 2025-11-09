# PIPEX Test Suite

## Organization

- `test_basic.sh` - Basic functionality tests (single/multiple commands)
- `test_errors.sh` - Error handling (invalid files, commands, permissions)
- `test_edge_cases.sh` - Edge cases (empty files, large files, special chars)
- `run_all.sh` - Master test runner

## Usage

Run all tests:
```bash
bash tests/run_all.sh
```

Run specific test suite:
```bash
bash tests/test_basic.sh
bash tests/test_errors.sh
bash tests/test_edge_cases.sh
```

## Expected Issues

Based on the current implementation:

1. **Command resolution** - `execve()` requires absolute paths, then falls back to `execvp()`
   - Should work but is inefficient
   
2. **Empty commands** - May not be properly validated

3. **Multiple spaces in commands** - `ft_split()` splits on single space, multiple spaces might cause issues

4. **Failed commands** - Error codes from failed commands in pipeline

## Test Coverage

- ✓ Single command
- ✓ Multiple commands (2, 3, 5+)
- ✓ Command with arguments/flags
- ✓ Nonexistent files
- ✓ Permission errors
- ✓ Invalid commands
- ✓ Empty files
- ✓ Large files
- ✓ Binary files
- ✓ Special characters
