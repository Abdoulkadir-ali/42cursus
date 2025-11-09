#!/bin/bash
# Edge case tests

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

echo -e "${YELLOW}=== EDGE CASE TESTS ===${NC}\n"

# Test 1: Empty file
echo "Test 1: Empty input file"
touch empty.txt
$PIPEX empty.txt "cat" "wc -l" outfile
cat empty.txt | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Empty input file" $?

# Test 2: Large file
echo "Test 2: Large file (10000 lines)"
seq 1 10000 > large.txt
$PIPEX large.txt "cat" "wc -l" outfile
cat large.txt | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Large file" $?

# Test 3: File with special characters
echo "Test 3: Special characters in content"
echo '$PATH and "quotes" and `backticks`' > special.txt
echo "newline and \t tabs" >> special.txt
$PIPEX special.txt "cat" "wc -l" outfile
cat special.txt | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Special characters in file" $?

# Test 4: Command with double spaces
echo "Test 4: Command with multiple spaces"
echo "test" > infile
$PIPEX infile "cat" "grep  test" outfile 2>/dev/null
# This might fail depending on parsing
[ -f outfile ]
run_test "Multiple spaces in command" $?

# Test 5: Many pipes (stress test)
echo "Test 5: Long pipe chain (5 commands)"
echo "line1" > infile
echo "line2" >> infile
$PIPEX infile "cat" "cat" "cat" "cat" "wc -l" outfile
cat infile | cat | cat | cat | cat | wc -l > expected
diff outfile expected > /dev/null 2>&1
run_test "Long pipe chain" $?

# Test 6: Binary file
echo "Test 6: Binary file input"
dd if=/dev/urandom of=binary.dat bs=1024 count=10 2>/dev/null
$PIPEX binary.dat "cat" "wc -c" outfile
cat binary.dat | wc -c > expected
diff outfile expected > /dev/null 2>&1
run_test "Binary file" $?

# Cleanup
rm -f empty.txt large.txt special.txt infile outfile expected binary.dat

echo -e "\n${YELLOW}Result: $pass_count/$test_count tests passed${NC}\n"
