*This project has been created as part of the 42 curriculum by abdoali.*

## Description

Push Swap is a 42 School algorithm project that challenges you to sort a stack of integers using only two stacks and a limited set of operations. The goal is to achieve perfect sorting with the minimum number of moves possible.

The project consists of two programs:
- **push_swap**: Takes a list of integers as arguments and outputs a sequence of operations to sort the stack in ascending order.
- **checker**: Takes the same list and a sequence of operations, then verifies if the operations correctly sort the stack.

This project demonstrates understanding of sorting algorithms, data structures (stacks), and optimization techniques in C programming.

## Instructions

### Prerequisites
- GCC compiler with C99 support
- Make build system
- Linux/Unix environment

### Compilation
```bash
# Build both push_swap and checker
make

# Build only push_swap
make push_swap

# Build only checker
make bonus

# Clean object files
make clean

# Clean all generated files
make fclean

# Rebuild everything
make re
```

### Execution
```bash
# Run push_swap with a list of numbers
./push_swap 4 2 8 1 3

# Pipe output to checker for validation
./push_swap 4 2 8 1 3 | ./checker 4 2 8 1 3

# Or use the provided checker
./push_swap 4 2 8 1 3 | ./checker_linux 4 2 8 1 3
```

### Testing
```bash
# Build and run tests
make test

# Run the test script
./tester.sh
```

## Resources

### Classic References
- [Push Swap Tutorial Video 1](https://www.youtube.com/watch?v=wRvipSG4Mmk): Educational video explaining push_swap concepts and basic operations
- [Push Swap Tutorial Video 2](https://www.youtube.com/watch?v=OaG81sDEpVk): Advanced push_swap techniques and algorithm implementations
- [42 Cursus Push Swap Guide](https://42-cursus.gitbook.io/guide/2-rank-02/push_swap): Official 42 school guide and documentation for the push_swap project
- [Push Swap: The Least Amount of Moves with Two Stacks](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a): In-depth article on optimizing push_swap algorithms for minimum operationsap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a): In-depth article on optimizing push_swap algorithms for minimum operations


### Utilisation de l'IA
L'IA a été utilisée pour aider à comprendre l'algorithme, au débogage, aux tests des cas limites, ainsi que dans la création d'un mini testeur en shell pour un auto-contrôle rapide.