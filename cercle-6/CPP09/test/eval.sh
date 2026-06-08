#!/bin/bash

# Configuration
NC='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." >/dev/null 2>&1 && pwd)"

function print_header() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}============  $1  ============${NC}"
    echo -e "${BLUE}========================================${NC}"
}

function expect() {
    local test_num=$1
    local name=$2
    local output=$3
    local expected=$4

    if [[ "$output" == *"$expected"* ]]; then
        echo -e "${GREEN}[PASS]${NC} Test $test_num: $name"
    else
        echo -e "${RED}[FAIL]${NC} Test $test_num: $name"
        echo -e "  Expected to contain: ${YELLOW}$expected${NC}"
        echo -e "  Got:\n${RED}$output${NC}"
    fi
}

echo "Compiling all exercises..."
make -C "$ROOT_DIR/ex00" > /dev/null 2>&1
make -C "$ROOT_DIR/ex01" > /dev/null 2>&1
make -C "$ROOT_DIR/ex02" > /dev/null 2>&1

print_header "EX00: Bitcoin Exchange"
cd "$ROOT_DIR/ex00"

# Provide subject files if missing for testing
printf "date,exchange_rate\n2009-01-02,0\n2011-01-03,0.3\n2011-01-08,0.32\n2012-01-11,7.1\n" > data.csv
printf "date | value\n2011-01-03 | 3\n2011-01-03 | 2\n2011-01-03 | 1\n2011-01-03 | 1.2\n2011-01-09 | 1\n2012-01-11 | -1\n2001-42-42\n2012-01-11 | 1\n2012-01-11 | 2147483648\n" > input.txt

res=$(./btc 2>&1)
expect "1" "No arguments" "$res" "Error: could not open file"

res=$(./btc nonexistent.txt 2>&1)
expect "2" "Missing file" "$res" "Error: could not open file"

res=$(./btc input.txt 2>&1)
expect "3" "Valid format calculation" "$res" "2011-01-03 => 3 = 0.9"
expect "4" "Bad date rejection" "$res" "Error: bad input => 2001-42-42"
expect "5" "Negative rejection" "$res" "Error: not a positive number"
expect "6" "Large number rejection" "$res" "Error: too large a number"


print_header "EX01: RPN"
cd "$ROOT_DIR/ex01"

res=$(./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" 2>&1)
expect "1" "Valid sequence (42)" "$res" "42"

res=$(./RPN "7 7 * 7 -" 2>&1)
expect "2" "Valid sequence (42)" "$res" "42"

res=$(./RPN "1 2 * 2 / 2 * 2 4 - +" 2>&1)
expect "3" "Valid mixed operations (0)" "$res" "0"

res=$(./RPN "(1 + 1)" 2>&1)
expect "4" "Bad tokens (brackets)" "$res" "Error"

res=$(./RPN "5 0 /" 2>&1)
expect "5" "Division by zero" "$res" "Error"


print_header "EX02: PmergeMe"
cd "$ROOT_DIR/ex02"

res=$(./PmergeMe 3 5 9 7 4 2>&1)
expect "1" "Sort sample elements (Before)" "$res" "Before: 3 5 9 7 4"
expect "2" "Sort sample elements (After)" "$res" "After: 3 4 5 7 9"
expect "3" "Timings printed (std::vector)" "$res" "Time to process a range of "
expect "4" "Timings printed (std::deque)" "$res" "std::deque"

res=$(./PmergeMe "-1" "2" 2>&1)
expect "5" "Negative arguments" "$res" "Error"

res=$(./PmergeMe 2 3 2 2>&1)
expect "6" "Duplicate arguments" "$res" "Error"

res=$(./PmergeMe invalid args 2>&1)
expect "7" "Non-digit arguments" "$res" "Error"

# Stress test 3000
echo -e "\nRunning 3000 element stress test..."
args=$(shuf -i 1-100000 -n 3000 | tr '\n' ' ')
res=$(./PmergeMe $args 2>&1 | wc -l)
if [ "$res" -ge 4 ]; then
    echo -e "${GREEN}[PASS]${NC} Stress test: produced 4 lines of output cleanly"
else
    echo -e "${RED}[FAIL]${NC} Stress test crashed or produced wrong line count."
fi

echo -e "\n${BLUE}Evaluation complete.${NC}"
