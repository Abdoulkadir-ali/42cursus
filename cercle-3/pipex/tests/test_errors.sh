#!/bin/bash
# Error handling tests

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

echo -e "${YELLOW}=== ERROR HANDLING TESTS ===${NC}\n"

# Setup
echo "test content" > infile

# Test 1: Nonexistent input file
echo "Test 1: Nonexistent input file"
$PIPEX nonexistent.txt "cat" "wc" outfile 2>/dev/null
[ $? -ne 0 ]
run_test "Nonexistent input file (should fail)" $?

# Test 2: No read permission on input
echo "Test 2: No read permission on input"
touch noread.txt
chmod 000 noread.txt
$PIPEX noread.txt "cat" "wc" outfile 2>/dev/null
result=$?
chmod 644 noread.txt
[ $result -ne 0 ]
run_test "No read permission (should fail)" $?

# Test 3: Invalid command
echo "Test 3: Invalid command"
$PIPEX infile "invalidcmd123" "wc" outfile 2>/dev/null
[ $? -ne 0 ]
run_test "Invalid command (should fail)" $?

# Test 4: Empty command string
echo "Test 4: Empty command"
$PIPEX infile "" "wc" outfile 2>/dev/null
[ $? -ne 0 ]
run_test "Empty command (should fail)" $?

# Test 5: Too few arguments
echo "Test 5: Too few arguments"
$PIPEX infile "cat" 2>/dev/null
[ $? -ne 0 ]
run_test "Too few arguments (should fail)" $?

# Test 6: Command that fails
echo "Test 6: Command that exits with error"
$PIPEX infile "grep nonexistent_pattern" "wc -l" outfile 2>/dev/null
# grep fails but pipeline should still work
[ -f outfile ]
run_test "Failed command in pipeline" $?

# Cleanup
rm -f infile outfile noread.txt

echo -e "\n${YELLOW}Result: $pass_count/$test_count tests passed${NC}\n"
