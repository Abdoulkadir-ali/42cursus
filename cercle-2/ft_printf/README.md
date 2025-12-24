# 🚀 FT_Printf - 42 School Project

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=makefile&logoColor=white)

**⭐ Master the Art of Formatted Output ⭐**

*Complete recreation of the printf function with custom formatting capabilities*

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)](https://github.com/your-username/ft_printf)
[![Norminette](https://img.shields.io/badge/norminette-passing-brightgreen?style=flat-square)](https://github.com/42School/norminette)
[![Score](https://img.shields.io/badge/score-100%2F100-brightgreen?style=flat-square)](#)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [🎮 Format Specifiers](#-format-specifiers)
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

### **The Formatting Master Challenge**

FT_Printf is a **42 School** project that challenges you to recreate the legendary **printf function** from scratch. Master string formatting, type conversion, and output manipulation!

🖨️ **Think you can handle any format specifier?** Prove your formatting prowess!

</div>

### 🎯 Project Goals

- **Core Functionality**: Implement basic format specifiers (%c, %s, %d, %i, %u, %x, %X, %p, %%)
- **Bonus Features**: Width, precision, flags (-, 0, ., #, +, space)
- **Type Handling**: Integers, strings, characters, pointers, hexadecimals
- **Memory Management**: No memory leaks, efficient allocation
- **Error Handling**: Robust parsing and conversion

---

## ✨ Features

<div align="center">

| 🚀 Feature | Description |
|------------|-------------|
| **🔢 Multiple Types** | Support for all standard C data types |
| **📏 Width & Precision** | Field width and decimal precision control |
| **🏴 Flags Support** | Left-align, zero-pad, alternate forms |
| **🔄 Type Conversion** | Automatic type conversion and formatting |
| **💾 Memory Safe** | Leak-free implementation with proper cleanup |
| **⚡ Performance** | Optimized output with minimal overhead |
| **🧪 Comprehensive Tests** | Extensive test suite for validation |
| **📚 Well Documented** | Clear code with detailed comments |

</div>

---

## 🎮 Format Specifiers

### Core Specifiers

| Specifier | Type | Description | Example |
|-----------|------|-------------|---------|
| `%c` | char | Single character | `ft_printf("%c", 'A')` → A |
| `%s` | string | String of characters | `ft_printf("%s", "Hello")` → Hello |
| `%d` | int | Signed decimal | `ft_printf("%d", 42)` → 42 |
| `%i` | int | Signed decimal | `ft_printf("%i", -42)` → -42 |
| `%u` | unsigned | Unsigned decimal | `ft_printf("%u", 42)` → 42 |
| `%x` | unsigned | Hex lowercase | `ft_printf("%x", 255)` → ff |
| `%X` | unsigned | Hex uppercase | `ft_printf("%X", 255)` → FF |
| `%p` | pointer | Memory address | `ft_printf("%p", ptr)` → 0x7fff... |
| `%%` | literal | Percent sign | `ft_printf("%%")` → % |

### Bonus Flags (Optional)

| Flag | Description | Example |
|------|-------------|---------|
| `-` | Left-align | `ft_printf("%-10s", "Hello")` → Hello     |
| `0` | Zero padding | `ft_printf("%010d", 42)` → 0000000042 |
| `.` | Precision | `ft_printf("%.2f", 3.14159)` → 3.14 |
| `#` | Alternate form | `ft_printf("%#x", 42)` → 0x2a |
| `+` | Show sign | `ft_printf("%+d", 42)` → +42 |
| ` ` | Space for positive | `ft_printf("% d", 42)` →  42 |

---

## 🏗️ Building

### Prerequisites
- **GCC**: GNU Compiler Collection
- **Make**: Build automation tool
- **libft**: Custom C library (included)

### Compilation
```bash
# Clone and navigate to project
cd ft_printf

# Build the library
make

# Build with bonus features
make bonus

# Clean object files
make clean

# Full clean
make fclean

# Rebuild everything
make re
```

### Library Usage
```c
// Include in your project
#include "ft_printf.h"

// Link with libftprintf.a
gcc your_file.c -L. -lftprintf -I includes/
```

---

## 🚀 Usage

### Basic Examples
```c
#include "ft_printf.h"

int main(void)
{
    // Basic usage
    ft_printf("Hello, %s!\n", "World");
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 255);

    // With flags
    ft_printf("Padded: %010d\n", 42);
    ft_printf("Width: %-10s\n", "Hello");

    return (0);
}
```

### Advanced Usage
```c
// Multiple arguments
ft_printf("%s scored %d points in %s\n", "Player", 100, "Game");

// Pointer addresses
int *ptr = &value;
ft_printf("Address: %p\n", ptr);

// Mixed types
ft_printf("Char: %c, String: %s, Int: %d\n", 'A', "test", 123);
```

---

## 📊 Implementation

### Architecture
```
ft_printf()
├── Parse format string
├── Handle flags and width
├── Convert arguments
└── Output formatted result

Core Functions:
├── ft_parse_format()    - Format string parsing
├── ft_handle_specifier() - Specifier processing
├── ft_convert_*()       - Type conversions
└── ft_output_*()        - Output formatting
```

### Key Components
- **Format Parser**: Analyzes format strings and extracts specifiers
- **Type Converters**: Handle different data type conversions
- **Output Manager**: Manages buffer and writes to stdout
- **Flag Processor**: Applies width, precision, and alignment flags

---

## 🧪 Testing

### Test Suite
```bash
# Run basic tests
make test

# Run comprehensive tests
make test_all

# Test with original printf comparison
make test_compare

# Memory leak testing
make test_leaks
```

### Test Categories
- **Basic Functionality**: Core specifiers working
- **Edge Cases**: NULL strings, extreme values
- **Flag Combinations**: Multiple flags together
- **Performance**: Speed and memory usage
- **Compatibility**: Matches original printf behavior

### Sample Test Output
```
Testing %s specifier...
✓ Basic string: "Hello World"
✓ NULL string: "(null)"
✓ Empty string: ""

Testing %d specifier...
✓ Positive: 42
✓ Negative: -42
✓ Zero: 0
✓ INT_MAX: 2147483647
✓ INT_MIN: -2147483648
```

---

## 📁 Project Structure

```
ft_printf/
├── Makefile                    # Build configuration
├── includes/
│   └── ft_printf.h            # Header file
├── srcs/
│   ├── printf/                # Core printf functions
│   │   ├── ft_printf.c
│   │   ├── ft_parse_format.c
│   │   ├── ft_handle_specifier.c
│   │   └── ft_output.c
│   ├── printf/bonus/          # Bonus features
│   │   ├── ft_flags.c
│   │   ├── ft_width.c
│   │   └── ft_precision.c
│   └── libft/                 # Required libft functions
│       ├── ft_atoi.c
│       ├── ft_strlen.c
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
NAME = libftprintf.a
INCLUDES = -I includes/

# Source files
SRCS = $(wildcard srcs/**/*.c)
```

### Customization
- **Buffer Size**: Adjust output buffer size in defines
- **Supported Types**: Add new format specifiers
- **Performance**: Optimize conversion algorithms

---

## 🤝 Contributing

<div align="center">

**42 School Project - Peer-to-peer evaluation encouraged!**

- 📝 **Code Reviews**: Submit your implementation for evaluation
- 🐛 **Bug Fixes**: Report and fix formatting edge cases
- 💡 **Optimizations**: Improve performance and memory usage
- 📚 **Documentation**: Enhance code comments and examples

</div>

---

## 🙏 Acknowledgments

<div align="center">

**Gratitude to:**

- **42 School** for the challenging printf recreation project
- **Peer students** for code reviews and feedback
- **C Standard Library** creators for the original printf inspiration

---

**Built with ❤️ at 42 School**

[![42 FT_Printf](https://img.shields.io/badge/42-FT_Printf-000000?style=for-the-badge&logo=42&logoColor=white)](#)

</div>