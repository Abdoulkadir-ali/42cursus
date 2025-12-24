# Push Swap

A 42 School project that implements an efficient sorting algorithm using two stacks and a limited set of operations.

## Overview

Push Swap is a sorting algorithm challenge that requires sorting a stack of integers using only two stacks (stack A and stack B) and a specific set of operations. The goal is to sort the stack with the minimum number of operations.

## Features

- **Efficient Sorting**: Implements advanced sorting algorithms for optimal performance
- **Stack Operations**: Supports all required push swap operations (push, swap, rotate, reverse rotate)
- **Input Validation**: Robust parsing and validation of input arguments
- **Checker Program**: Validates sorting sequences and checks correctness
- **Comprehensive Testing**: Built-in test suite for all components
- **Debug Mode**: Visual debugging output for development

## Operations

The program uses the following operations:

- `sa` / `sb` / `ss`: Swap the first two elements of stack A/B/both
- `pa` / `pb`: Push top element from stack B/A to stack A/B
- `ra` / `rb` / `rr`: Rotate stack A/B/both upward
- `rra` / `rrb` / `rrr`: Reverse rotate stack A/B/both downward

## Building the Project

### Prerequisites

- GCC compiler with C99 support
- Make build system
- Standard C library

### Compilation

```bash
# Build the main program and checker
make

# Build only the push_swap program
make push_swap

# Build only the checker program
make checker

# Build all test programs
make test

# Clean object files
make clean

# Clean everything including executables
make fclean

# Rebuild everything
make re
```

## Usage

### Push Swap Program

Sort a list of integers:

```bash
# Single argument with space-separated numbers
./push_swap "4 2 8 1 3"

# Multiple arguments
./push_swap 4 2 8 1 3

# Large input (500 numbers)
./push_swap $(seq 1 500 | sort -R)
```

### Checker Program

Validate a sequence of operations:

```bash
# Check if operations sort the stack correctly
./push_swap 3 2 1 | ./checker 3 2 1

# Manual input of operations
echo -e "sa\npb\npa" | ./checker 2 1

# Using the provided checker_linux
./push_swap 3 2 1 | ./checker_linux 3 2 1
```

### Test Programs

Run individual component tests:

```bash
# Test argument parsing
./tests/parser 1 5 34 "4145 4514 14515" 8 48

# Test stack operations
./tests/move

# Test sorting algorithm
./tests/algo

# Test cost calculation
./tests/cost

# Test target finding
./tests/target
```

## Input Format

- **Numbers**: Integers between `INT_MIN` (-2147483648) and `INT_MAX` (2147483647)
- **Duplicates**: Not allowed (program will exit with error)
- **Format**: Space-separated numbers, can be positive or negative
- **Signs**: Multiple consecutive signs are handled (e.g., `++123`, `--456`)

### Valid Examples

```bash
./push_swap 1 2 3 4 5          # Already sorted
./push_swap 5 4 3 2 1          # Reverse sorted
./push_swap -5 0 10 -20 42     # Mixed positive/negative
./push_swap "1 2 3" "4 5 6"    # Multiple arguments
./push_swap "++1 --2 +++3"     # Multiple signs
```

### Invalid Examples

```bash
./push_swap                    # No arguments
./push_swap 1 2 2 3            # Duplicates
./push_swap 1 2 abc 4          # Non-numeric input
./push_swap 999999999999       # Out of int range
```

## Algorithm Overview

The sorting algorithm uses several strategies:

1. **Small Sorts**: Direct sorting for stacks of size 2-5
2. **Chunk Sorting**: Divides large stacks into chunks for efficient sorting
3. **Cost Optimization**: Calculates optimal moves to minimize total operations
4. **Target Finding**: Determines best positions for elements in both stacks

## Project Structure

```
push_swap/
├── includes/              # Header files
│   └── push_swap.h       # Main header with structures and macros
├── srcs/
│   ├── libft/           # Custom C library
│   └── push_swap/       # Main source code
│       ├── algo/        # Sorting algorithms
│       │   ├── cost/    # Cost calculation
│       │   ├── sort/    # Sorting logic
│       │   └── target/  # Target position finding
│       ├── checker/     # Checker program
│       ├── helper/      # Utility functions
│       │   ├── display/ # Debug output
│       │   ├── lst/     # Linked list operations
│       │   └── stacks/  # Stack management
│       ├── main/        # Main program entry
│       ├── moves/       # Stack operations
│       └── parsing/     # Input parsing
│           ├── moves/   # Operation parsing
│           └── stacks/  # Number parsing
├── obj/                 # Object files (generated)
├── tests/               # Test executables (generated)
├── Makefile            # Build configuration
├── checker_linux       # Provided checker binary
├── push_swap           # Main executable (generated)
└── tester.sh          # Test script
```

## Configuration

The program includes several configuration options in `push_swap.h`:

- `DEBUG`: Enable/disable debug output (0/1)
- `MULTIPLE_SIGN_INVALID`: Allow/disallow multiple signs (0/1)
- `CHUNK_SIZE_*`: Chunk sizes for different input ranges

## Performance

The algorithm is optimized for different input sizes:

- **Small (≤ 5)**: Direct sorting, minimal operations
- **Medium (6-100)**: Chunk-based sorting with cost optimization
- **Large (101-500)**: Advanced chunking with position optimization

## Error Handling

The program handles various error conditions:

- Invalid arguments
- Duplicate numbers
- Non-numeric input
- Memory allocation failures
- Invalid operations (in checker mode)

## Development

### Adding New Operations

1. Add operation function in `moves/`
2. Update `execute_instruction()` in algorithm files
3. Add to test cases in `tests/move`

### Modifying Algorithms

1. Edit sorting logic in `algo/sort/`
2. Update cost calculations in `algo/cost/`
3. Test with various input sizes

### Debug Mode

Enable debug output by setting `DEBUG=1` in the header:

```c
#define DEBUG 1
```

This will show stack states after each operation.

## Testing

Use the provided test script:

```bash
./tester.sh
```

Or run individual tests:

```bash
# Test with 100 random numbers
./push_swap $(seq 1 100 | sort -R) | wc -l

# Validate with checker
./push_swap $(seq 1 100 | sort -R) | ./checker_linux $(seq 1 100 | sort -R)
```

## License

This project is part of the 42 School curriculum. All rights reserved to 42 School.

## Author

[Your Name] - 42 School student</content>
<parameter name="filePath">/home/abdoali/Documents/42cursus/cercle-3/push_swap/README.md