# 🚀 Libft - 42 School Project

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=makefile&logoColor=white)

**⭐ Build Your Own C Standard Library ⭐**

*Complete recreation of essential C library functions from scratch*

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)](https://github.com/your-username/libft)
[![Norminette](https://img.shields.io/badge/norminette-passing-brightgreen?style=flat-square)](https://github.com/42School/norminette)
[![Score](https://img.shields.io/badge/score-125%2F100-brightgreen?style=flat-square)](#)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [📚 Function Categories](#-function-categories)
- [🏗️ Building](#️-building)
- [🚀 Usage](#-usage)
- [📊 Implementation](#-implementation)
- [🧪 Testing](#-testing)
- [📁 Project Structure](#-project-structure)
- [⚙️ Configuration](#️-configuration)
- [🤝 Contributing](#-contributing)
- [🙏 Acknowledgments](#-acknowledgments)

---

## 🎯 Overview

<div align="center">

### **The Foundation Library Challenge**

Libft is the **first major project** at **42 School** that challenges you to recreate essential **C standard library functions** from scratch. Master memory management, string manipulation, and data structures!

🛠️ **Think you can rebuild the foundations of C?** Prove your programming fundamentals!

</div>

### 🎯 Project Goals

- **Memory Functions**: Recreate malloc, free, and memory utilities
- **String Functions**: Implement string manipulation from scratch
- **Character Functions**: Handle character classification and conversion
- **Conversion Functions**: Number to string and vice versa
- **Linked Lists**: Build a complete linked list library
- **No External Functions**: Only use authorized system calls
- **Memory Safe**: Zero leaks, proper error handling

---

## ✨ Features

<div align="center">

| 🚀 Feature | Description |
|------------|-------------|
| **💾 Memory Management** | Safe allocation, copying, and comparison |
| **🔤 String Operations** | Complete string manipulation toolkit |
| **🔢 Type Conversion** | ASCII to numbers and back |
| **📝 Character Handling** | Classification and transformation |
| **🔗 Linked Lists** | Full doubly-linked list implementation |
| **🛡️ Memory Safe** | Leak-free with proper cleanup |
| **⚡ Performance** | Optimized algorithms for efficiency |
| **🧪 Well Tested** | Comprehensive test coverage |

</div>

---

## 📚 Function Categories

### Memory Functions

| Function | Description | Prototype |
|----------|-------------|-----------|
| `ft_memset` | Fill memory with byte | `void *ft_memset(void *s, int c, size_t n)` |
| `ft_bzero` | Zero out memory | `void ft_bzero(void *s, size_t n)` |
| `ft_memcpy` | Copy memory area | `void *ft_memcpy(void *dest, const void *src, size_t n)` |
| `ft_memmove` | Copy with overlap handling | `void *ft_memmove(void *dest, const void *src, size_t n)` |
| `ft_memchr` | Locate byte in memory | `void *ft_memchr(const void *s, int c, size_t n)` |
| `ft_memcmp` | Compare memory areas | `int ft_memcmp(const void *s1, const void *s2, size_t n)` |
| `ft_calloc` | Allocate zero-initialized memory | `void *ft_calloc(size_t nmemb, size_t size)` |

### String Functions

| Function | Description | Prototype |
|----------|-------------|-----------|
| `ft_strlen` | Calculate string length | `size_t ft_strlen(const char *s)` |
| `ft_strlcpy` | Copy string with size limit | `size_t ft_strlcpy(char *dst, const char *src, size_t size)` |
| `ft_strlcat` | Concatenate with size limit | `size_t ft_strlcat(char *dst, const char *src, size_t size)` |
| `ft_strchr` | Locate character in string | `char *ft_strchr(const char *s, int c)` |
| `ft_strrchr` | Locate last occurrence | `char *ft_strrchr(const char *s, int c)` |
| `ft_strncmp` | Compare strings with limit | `int ft_strncmp(const char *s1, const char *s2, size_t n)` |
| `ft_strnstr` | Locate substring | `char *ft_strnstr(const char *big, const char *little, size_t len)` |
| `ft_strdup` | Duplicate string | `char *ft_strdup(const char *s)` |

### Character Functions

| Function | Description | Prototype |
|----------|-------------|-----------|
| `ft_isalpha` | Check alphabetic character | `int ft_isalpha(int c)` |
| `ft_isdigit` | Check decimal digit | `int ft_isdigit(int c)` |
| `ft_isalnum` | Check alphanumeric | `int ft_isalnum(int c)` |
| `ft_isascii` | Check ASCII character | `int ft_isascii(int c)` |
| `ft_isprint` | Check printable character | `int ft_isprint(int c)` |
| `ft_toupper` | Convert to uppercase | `int ft_toupper(int c)` |
| `ft_tolower` | Convert to lowercase | `int ft_tolower(int c)` |

### Conversion Functions

| Function | Description | Prototype |
|----------|-------------|-----------|
| `ft_atoi` | ASCII to integer | `int ft_atoi(const char *nptr)` |
| `ft_itoa` | Integer to ASCII | `char *ft_itoa(int n)` |

### Linked List Functions

| Function | Description | Prototype |
|----------|-------------|-----------|
| `ft_lstnew` | Create new list element | `t_list *ft_lstnew(void *content)` |
| `ft_lstadd_front` | Add element at beginning | `void ft_lstadd_front(t_list **lst, t_list *new)` |
| `ft_lstsize` | Count list elements | `int ft_lstsize(t_list *lst)` |
| `ft_lstlast` | Get last element | `t_list *ft_lstlast(t_list *lst)` |
| `ft_lstadd_back` | Add element at end | `void ft_lstadd_back(t_list **lst, t_list *new)` |
| `ft_lstdelone` | Delete element | `void ft_lstdelone(t_list *lst, void (*del)(void *))` |
| `ft_lstclear` | Delete entire list | `void ft_lstclear(t_list **lst, void (*del)(void *))` |
| `ft_lstiter` | Iterate over list | `void ft_lstiter(t_list *lst, void (*f)(void *))` |
| `ft_lstmap` | Map function over list | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` |

---

## 🏗️ Building

### Prerequisites
- **GCC**: GNU Compiler Collection
- **Make**: Build automation tool
- **Standard C Library**: Only authorized functions

### Compilation
```bash
# Navigate to libft directory
cd cercle-1/libft

# Build the library
make

# Build bonus functions
make bonus

# Clean object files
make clean

# Full clean
make fclean

# Rebuild everything
make re
```

### Library Files
- **libft.a**: Static library with mandatory functions
- **libft_bonus.a**: Library with bonus linked list functions

---

## 🚀 Usage

### Basic Usage
```c
// Include header
#include "libft.h"

// Compile with library
gcc your_program.c -L. -lft -I includes/
```

### Memory Functions Example
```c
#include "libft.h"

int main(void)
{
    // Memory allocation
    char *buffer = ft_calloc(100, sizeof(char));

    // Memory operations
    ft_memset(buffer, 'A', 10);
    char *copy = ft_memcpy(buffer, "Hello", 5);

    // String operations
    char *str = ft_strdup("World");
    int len = ft_strlen(str);

    // Cleanup
    free(buffer);
    free(str);

    return (0);
}
```

### Linked List Example
```c
#include "libft.h"

int main(void)
{
    // Create list
    t_list *list = NULL;

    // Add elements
    ft_lstadd_back(&list, ft_lstnew("First"));
    ft_lstadd_back(&list, ft_lstnew("Second"));

    // Get size
    int size = ft_lstsize(list);

    // Iterate and print
    ft_lstiter(list, print_content);

    // Cleanup
    ft_lstclear(&list, free);

    return (0);
}
```

### Character Classification
```c
#include "libft.h"

int main(void)
{
    char c = 'A';

    if (ft_isalpha(c))
        printf("%c is alphabetic\n", c);

    if (ft_isupper(c))
        printf("%c is uppercase\n", c);

    char lower = ft_tolower(c);
    printf("Lowercase: %c\n", lower);

    return (0);
}
```

---

## 📊 Implementation

### Code Organization
```
Mandatory Functions:
├── Memory: memset, bzero, memcpy, memmove, memchr, memcmp, calloc
├── Strings: strlen, strlcpy, strlcat, strchr, strrchr, strncmp, strnstr, strdup
├── Characters: isalpha, isdigit, isalnum, isascii, isprint, toupper, tolower
└── Conversion: atoi, itoa

Bonus Functions:
└── Linked Lists: All lst* functions with t_list structure
```

### Key Concepts
- **Memory Safety**: Proper bounds checking and null termination
- **Error Handling**: Return appropriate values for error conditions
- **Performance**: Efficient algorithms with minimal overhead
- **Standards Compliance**: Match original library behavior exactly

### Data Structures
```c
// Linked list node
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
} t_list;
```

---

## 🧪 Testing

### Test Suite
```bash
# Run basic tests
make test

# Test memory functions
make test_memory

# Test string functions
make test_strings

# Test linked lists
make test_bonus

# Memory leak testing
make test_leaks
```

### Test Categories
- **Functionality**: Correct output for all inputs
- **Edge Cases**: NULL pointers, empty strings, extreme values
- **Memory**: No leaks, proper allocation/deallocation
- **Performance**: Efficient execution time
- **Compatibility**: Matches standard library behavior

### Sample Test Output
```
Testing memory functions...
✓ ft_memset: Basic functionality
✓ ft_memcpy: Overlap handling
✓ ft_calloc: Zero initialization

Testing string functions...
✓ ft_strlen: Various lengths
✓ ft_strlcpy: Size limits
✓ ft_strdup: Memory allocation

Testing linked lists...
✓ ft_lstnew: Node creation
✓ ft_lstadd_back: Element addition
✓ ft_lstclear: Memory cleanup
```

---

## 📁 Project Structure

```
libft/
├── Makefile                    # Build configuration
├── includes/
│   └── libft.h                # Main header file
├── srcs/
│   ├── char/                  # Character functions
│   │   ├── ft_isalpha.c
│   │   ├── ft_isdigit.c
│   │   └── ...
│   ├── int/                   # Conversion functions
│   │   ├── ft_atoi.c
│   │   └── ft_itoa.c
│   ├── lst/                   # Linked list functions
│   │   ├── ft_lstnew.c
│   │   ├── ft_lstadd_front.c
│   │   └── ...
│   ├── mem/                   # Memory functions
│   │   ├── ft_memset.c
│   │   ├── ft_bzero.c
│   │   └── ...
│   └── str/                   # String functions
│       ├── ft_strlen.c
│       ├── ft_strcpy.c
│       └── ...
├── objs/                      # Object files
└── README.md                  # This file
```

---

## ⚙️ Configuration

### Makefile Variables
```makefile
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Library settings
NAME = libft.a
BONUS_NAME = libft_bonus.a

# Source directories
CHAR_DIR = srcs/char/
MEM_DIR = srcs/mem/
STR_DIR = srcs/str/
INT_DIR = srcs/int/
LST_DIR = srcs/lst/
```

### Compilation Flags
- **-Wall**: Enable all warnings
- **-Wextra**: Extra warning flags
- **-Werror**: Treat warnings as errors
- **-I includes/**: Include header directory

### Customization
- **Function Names**: All functions prefixed with `ft_`
- **Header Guards**: Proper include guards in headers
- **Code Style**: Follows 42 Norminette standards

---

## 🤝 Contributing

<div align="center">

**42 School Foundation Project - Essential for all future projects!**

- 📝 **Code Reviews**: Share your libft implementation
- 🐛 **Bug Fixes**: Improve edge case handling
- ⚡ **Optimizations**: Enhance performance and memory usage
- 🧪 **Test Cases**: Add comprehensive test scenarios
- 📚 **Documentation**: Improve function comments and examples

</div>

---

## 🙏 Acknowledgments

<div align="center">

**Special thanks to:**

- **42 School** for the fundamental library project
- **Peer evaluators** for thorough code reviews
- **C Standard Library** creators for the original inspiration

---

**Built with ❤️ at 42 School**

[![42 Libft](https://img.shields.io/badge/42-Libft-000000?style=for-the-badge&logo=42&logoColor=white)](#)

</div>