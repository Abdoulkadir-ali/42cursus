#!/bin/bash
# Master test runner

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════╗${NC}"
echo -e "${BLUE}║      PIPEX TEST SUITE              ║${NC}"
echo -e "${BLUE}╔════════════════════════════════════╗${NC}\n"

# Check if pipex exists
if [ ! -f "./pipex" ]; then
    echo -e "${RED}Error: pipex executable not found!${NC}"
    echo "Run 'make' first to compile the project."
    exit 1
fi

# Make test scripts executable
chmod +x tests/*.sh

total_passed=0
total_failed=0

# Run all test suites
for test_file in tests/test_*.sh; do
    if [ -f "$test_file" ]; then
        echo -e "${BLUE}Running $(basename $test_file)...${NC}"
        bash "$test_file"
        echo ""
    fi
done

echo -e "${BLUE}╔════════════════════════════════════╗${NC}"
echo -e "${BLUE}║      ALL TESTS COMPLETE            ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════╝${NC}"
