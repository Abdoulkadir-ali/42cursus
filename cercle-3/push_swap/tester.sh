#!/bin/bash

# Default values if no arguments provided
LIST_LEN=${1:-100}
ITERATIONS=${2:-10}

# Paths (Edit if your checker has a different name)
PUSH_SWAP="./push_swap"
CHECKER="./checker_linux" # Or your own ./checker if you made one
BONUS_CHECKER="./checker" # Your own bonus checker

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

# Check if checker exists and is executable
if [ -f "$CHECKER" ]; then
    if [ ! -x "$CHECKER" ]; then
        echo -e "${YELLOW}Warning: $CHECKER is not executable. Making it executable...${RESET}"
        chmod +x "$CHECKER" 2>/dev/null || {
            echo -e "${RED}Error: Cannot make $CHECKER executable. Please run: chmod +x $CHECKER${RESET}"
            exit 1
        }
    fi
else
    echo -e "${YELLOW}Warning: $CHECKER not found. Sorting validation will be skipped.${RESET}"
fi

# Check if bonus checker exists and is executable
if [ -f "$BONUS_CHECKER" ]; then
    if [ ! -x "$BONUS_CHECKER" ]; then
        echo -e "${YELLOW}Warning: $BONUS_CHECKER is not executable. Making it executable...${RESET}"
        chmod +x "$BONUS_CHECKER" 2>/dev/null || {
            echo -e "${YELLOW}Warning: Cannot make $BONUS_CHECKER executable.${RESET}"
        }
    fi
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
    BONUS_STATUS=""
    
    if [ -f "$CHECKER" ]; then
        CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG 2>&1)
        if [ "$CHECK_RESULT" == "OK" ]; then
            STATUS="${GREEN}[OK]${RESET}"
        elif [ "$CHECK_RESULT" == "KO" ]; then
            STATUS="${RED}[KO - NOT SORTED]${RESET}"
            echo ""
            echo -e "${RED}╔════════════════════════════════════════════════╗${RESET}"
            echo -e "${RED}║  ERROR: List not properly sorted on run $i!   ║${RESET}"
            echo -e "${RED}╚════════════════════════════════════════════════╝${RESET}"
            echo -e "${YELLOW}Arguments:${RESET} $ARG"
            echo -e "${YELLOW}Moves:${RESET} $MOVES"
            echo -e "${YELLOW}Checker result:${RESET} KO"
            echo ""
            echo -e "${RED}Aborting test suite.${RESET}"
            exit 1
        else
            STATUS="${RED}[ERROR]${RESET}"
            echo ""
            echo -e "${RED}╔════════════════════════════════════════════════╗${RESET}"
            echo -e "${RED}║  ERROR: Checker returned unexpected result!   ║${RESET}"
            echo -e "${RED}╚════════════════════════════════════════════════╝${RESET}"
            echo -e "${YELLOW}Arguments:${RESET} $ARG"
            echo -e "${YELLOW}Checker output:${RESET} $CHECK_RESULT"
            echo ""
            echo -e "${RED}Aborting test suite.${RESET}"
            exit 1
        fi
    fi
    
    # Bonus checker verification
    if [ -f "$BONUS_CHECKER" ] && [ -x "$BONUS_CHECKER" ]; then
        BONUS_RESULT=$($PUSH_SWAP $ARG | $BONUS_CHECKER $ARG 2>&1)
        if [ "$BONUS_RESULT" == "OK" ]; then
            BONUS_STATUS="${GREEN}[OK]${RESET}"
        elif [ "$BONUS_RESULT" == "KO" ]; then
            BONUS_STATUS="${RED}[KO]${RESET}"
            echo ""
            echo -e "${RED}╔════════════════════════════════════════════════╗${RESET}"
            echo -e "${RED}║  ERROR: Bonus checker failed on run $i!       ║${RESET}"
            echo -e "${RED}╚════════════════════════════════════════════════╝${RESET}"
            echo -e "${YELLOW}Arguments:${RESET} $ARG"
            echo -e "${YELLOW}Moves:${RESET} $MOVES"
            echo -e "${YELLOW}Bonus checker result:${RESET} KO"
            echo ""
            echo -e "${RED}Aborting test suite.${RESET}"
            exit 1
        else
            BONUS_STATUS="${RED}[ERR]${RESET}"
        fi
    fi

    # Update Stats
    TOTAL=$((TOTAL + MOVES))
    if (( MOVES < MIN )); then MIN=$MOVES; fi
    if (( MOVES > MAX )); then MAX=$MOVES; fi

    # Print current run
    printf "Run %2d: ${YELLOW}%4d${RESET} moves %b %b\n" "$i" "$MOVES" "$STATUS" "$BONUS_STATUS"
done

# Calculate Average
AVG=$((TOTAL / ITERATIONS))

echo "------------------------------------------------"
echo -e "${BLUE}RESULTS FOR $LIST_LEN NUMBERS:${RESET}"
echo -e "Min: ${GREEN}$MIN${RESET}"
echo -e "Max: ${RED}$MAX${RESET}"
echo -e "Avg: ${YELLOW}$AVG${RESET}"
