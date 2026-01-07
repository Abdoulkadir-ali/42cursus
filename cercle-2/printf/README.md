*This project has been created as part of the 42 curriculum by abdoali.*

# ft_printf

## Description

The goal of this project is to reimplement the standard C library function `printf`. This project provides a deep understanding of variadic functions (`stdarg.h`) and data formatting in C.

The `ft_printf` function parses a formatted string and prints arguments to the standard output, managing various conversions and flags including width, precision, and length modifiers.

## Instructions

### Compilation

To compile the project and generate the static library `libftprintf.a`, run:
```bash
make
```

Other available commands in the Makefile:
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the library.
- `make re`: Recompiles the project from scratch.
- `make bonus`: (If available) Compiles and runs tests using `printfTester`.

### Usage

To use `ft_printf` in your project, include the header file and link against the library.

**Example `main.c`:**
```c
#include "includes/ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! The answer is %d.\n", "world", 42);
    ft_printf("Hexadecimal: %x\n", 255);
    return (0);
}
```

**Compiling with your code:**
```bash
gcc main.c -L. -lftprintf -o main
./main
```

## Resources

- `man 3 printf`
- `man 3 stdarg`
- [Variadic Functions in C](https://en.cppreference.com/w/c/variadic)

### AI Usage
AI (GitHub Copilot) was used to generate this `README.md` file to meet the project's documentation requirements, synthesizing information from the project's source code and file structure.

## Algorithm and Data Structure

The implementation of `ft_printf` is modular, separating the parsing of format specifiers from the actual printing logic.

### Data Structure: `t_flags`
A custom structure `t_flags` (defined in `includes/ft_printf.h`) is used to store all parsing information for a single format specifier.

```c
typedef struct s_flags
{
    size_t      hash;       // # flag
    size_t      space;      // Space flag
    size_t      dot;        // . flag (precision indicator)
    size_t      plus;       // + flag
    size_t      minus;      // - flag
    size_t      zero;       // 0 flag
    size_t      precision;  // Precision value
    size_t      width;      // Field width
    size_t      length;     // Length modifier (l, ll, h, hh)
}               t_flags;
```

This structure allows the parsers to populate the state cleanly before any printing occurs.

### Algorithm Steps

1.  **Main Loop (`ft_printf.c`)**:
    -   The function iterates through the input format string.
    -   Standard characters are printed immediately to the buffer/output.
    -   When a `%` is encountered, the control is passed to `ft_handle_flags`.

2.  **Parsing (`srcs/parsers/`)**:
    -   `ft_handle_flags` calls `ft_build_flags`.
    -   **Flag Parsing**: `ft_parse_flags` detects flags like ` -`, `0`, `#`, ` `, `+`.
    -   **Width & Precision**: `ft_parse_width` and `ft_parse_precision` extract numerical values or `*` arguments.
    -   **Length Modifiers**: `ft_parse_length` detects modifiers like `l`, `ll`, `h`.
    -   All extracted data is stored in the `t_flags` struct.

3.  **Dispatching (`srcs/handlers/main.c`)**:
    -   After parsing, `ft_handle_flags` determines the conversion specifier (e.g., `c`, `s`, `d`, `x`).
    -   It calls `dispatch_handler`, which routes the request to the specific handler function (e.g., `ft_handle_nbr`, `ft_handle_str`).

4.  **Handling and Printing (`srcs/handlers/`)**:
    -   Each handler function (e.g., `ft_handle_nbr`) calculates the final length of the output, considering the number of digits, padding (width), and precision.
    -   Helper functions in `srcs/helpers/` (like `ft_putchar`, `ft_putstr`) are used to perform the actual write operations.
    -   The total count of characters printed is returned up the call stack and accumulated in `ft_printf`.

This modular approach ensures that adding new flags or conversion specifiers is straightforward and keeps the logic for each component isolated and maintainable.
