#!/bin/bash
# Basic functionality tests

PIPEX="./pipex"
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

test_count=0
pass_count=0

run_test() {
    local test_name="$1"
    local result="$2"
    
    test_count=$((test_count + 1))
    if [ $result -eq 0 ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        pass_count=$((pass_count + 1))
    else
        echo -e "${RED}✗${NC} $test_name"
    fi
}

echo -e "${YELLOW}=== BASIC TESTS ===${NC}\n"

# Setup
echo "line1" > infile
echo "line2" >> infile
echo "line3" >> infile

# Test 1: Single command
echo "Test 1: Single command (cat)"
$PIPEX infile "cat" outfile
cat infile > expected
diff outfile expected > /dev/null 2>&1
run_test "Single command" $?

# Test 2: Two commands
echo "Test 2: Two commands (cat | wc -l)"
$PIPEX infile "cat" "wc -l" outfile
cat infile | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Two commands" $?

# Test 3: Three commands
echo "Test 3: Three commands (cat | grep line | wc -l)"
$PIPEX infile "cat" "grep line" "wc -l" outfile
cat infile | grep line | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Three commands" $?

# Test 4: Command with multiple arguments
echo "Test 4: Command with flags (ls -la)"
touch testfile1 testfile2
$PIPEX infile "ls -l" "wc -l" outfile
ls -l | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Command with flags" $?

# Test 5: grep with pattern
echo "Test 5: grep pattern"
$PIPEX infile "grep line" "wc -l" outfile
cat infile | grep line | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "grep pattern" $?

# Cleanup
rm -f infile outfile expected testfile1 testfile2

echo -e "\n${YELLOW}Result: $pass_count/$test_count tests passed${NC}\n"
