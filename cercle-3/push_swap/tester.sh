#!/bin/bash

# Default values if no arguments provided
LIST_LEN=${1:-100}
ITERATIONS=${2:-10}

# Paths (Edit if your checker has a different name)
PUSH_SWAP="./push_swap"
CHECKER="./checker_linux" # Or your own ./checker if you made one

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RESET='\033[0m'

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: $PUSH_SWAP not found. Please compile first.${RESET}"
    exit 1
fi

echo -e "${BLUE}Testing push_swap with $LIST_LEN numbers for $ITERATIONS iterations...${RESET}"
echo "------------------------------------------------"

# Variables for statistics
MIN=999999999
MAX=-1
TOTAL=0

for ((i=1; i<=ITERATIONS; i++)); do
    # Generate random numbers
    ARG=$(seq 1 $LIST_LEN | shuf | tr '\n' ' ')
    
    # Run push_swap and count moves
    MOVES=$($PUSH_SWAP $ARG | wc -l)
    
    # Verification (Optional: only if checker exists)
    STATUS=""
    if [ -f "$CHECKER" ]; then
        CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
        if [ "$CHECK_RESULT" == "OK" ]; then
            STATUS="${GREEN}[OK]${RESET}"
        else
            STATUS="${RED}[KO]${RESET}"
            echo -e "${RED}Error: List not sorted on run $i!${RESET}"
            echo "Args: $ARG"
            exit 1
        fi
    fi

    # Update Stats
    TOTAL=$((TOTAL + MOVES))
    if (( MOVES < MIN )); then MIN=$MOVES; fi
    if (( MOVES > MAX )); then MAX=$MOVES; fi

    # Print current run
    printf "Run %2d: ${YELLOW}%4d${RESET} moves %b\n" "$i" "$MOVES" "$STATUS"
done

# Calculate Average
AVG=$((TOTAL / ITERATIONS))

echo "------------------------------------------------"
echo -e "${BLUE}RESULTS FOR $LIST_LEN NUMBERS:${RESET}"
echo -e "Min: ${GREEN}$MIN${RESET}"
echo -e "Max: ${RED}$MAX${RESET}"
echo -e "Avg: ${YELLOW}$AVG${RESET}"