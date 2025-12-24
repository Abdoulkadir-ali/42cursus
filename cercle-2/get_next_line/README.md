# 🚀 Get_Next_Line - 42 School Project

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=makefile&logoColor=white)

**⭐ Master File Reading Line by Line ⭐**

*Efficient line-by-line file reading with static variables and buffer management*

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)](https://github.com/your-username/get_next_line)
[![Norminette](https://img.shields.io/badge/norminette-passing-brightgreen?style=flat-square)](https://github.com/42School/norminette)
[![Score](https://img.shields.io/badge/score-125%2F100-brightgreen?style=flat-square)](#)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [🏗️ Building](#️-building)
- [🚀 Usage](#-usage)
- [📊 Implementation](#-implementation)
- [🎮 Bonus Features](#-bonus-features)
- [🧪 Testing](#-testing)
- [📁 Project Structure](#-project-structure)
- [⚙️ Configuration](#️-configuration)
- [🤝 Contributing](#-contributing)
- [🙏 Acknowledgments](#-acknowledgments)

---

## 🎯 Overview

<div align="center">

### **The File Reading Challenge**

Get_Next_Line is a **42 School** project that challenges you to create a function that reads a file **line by line** efficiently. Master static variables, buffer management, and file descriptor handling!

📖 **Think you can read any file smoothly?** Prove your file I/O mastery!

</div>

### 🎯 Project Goals

- **Line-by-Line Reading**: Read files one line at a time
- **Buffer Management**: Efficient buffer handling with defined size
- **Static Variables**: Preserve state between function calls
- **Multiple FDs**: Handle multiple file descriptors simultaneously
- **Memory Management**: No memory leaks, proper cleanup
- **Error Handling**: Robust error checking and recovery

---

## ✨ Features

<div align="center">

| 🚀 Feature | Description |
|------------|-------------|
| **📖 Line Reading** | Read files line by line efficiently |
| **🔄 Static State** | Preserve reading state between calls |
| **📏 Buffer Control** | Configurable buffer size (1-INT_MAX) |
| **🔢 Multiple FDs** | Handle multiple file descriptors |
| **💾 Memory Safe** | Leak-free with proper memory management |
| **⚡ Performance** | Optimized reading with minimal overhead |
| **🛡️ Error Handling** | Robust error checking and recovery |
| **🎯 Bonus Ready** | Extensible for advanced features |

</div>

---

## 🏗️ Building

### Prerequisites
- **GCC**: GNU Compiler Collection
- **Make**: Build automation tool
- **Standard C Library**: File I/O functions

### Compilation
```bash
# Navigate to project directory
cd get_next_line

# Build mandatory part
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
#include "get_next_line.h"

// Compile with source files
gcc your_program.c get_next_line.c get_next_line_utils.c
```

---

## 🚀 Usage

### Basic Usage
```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    // Open file
    fd = open("example.txt", O_RDONLY);

    // Read line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free!
    }

    // Close file
    close(fd);
    return (0);
}
```

### Multiple Files
```c
// Handle multiple file descriptors
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1;
char *line2;

while (1)
{
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    if (!line1 && !line2)
        break;

    if (line1)
    {
        printf("File1: %s", line1);
        free(line1);
    }
    if (line2)
    {
        printf("File2: %s", line2);
        free(line2);
    }
}
```

### Error Handling
```c
// Always check for errors
char *line;
int fd = open("nonexistent.txt", O_RDONLY);

if (fd == -1)
{
    perror("Error opening file");
    return (1);
}

while ((line = get_next_line(fd)) != NULL)
{
    // Process line
    free(line);
}

if (close(fd) == -1)
{
    perror("Error closing file");
}
```

---

## 📊 Implementation

### Core Function
```c
char *get_next_line(int fd);
```

### Key Concepts
- **Static Variables**: Preserve buffer state between calls
- **Buffer Management**: Read chunks and assemble lines
- **Newline Detection**: Find and extract complete lines
- **Memory Cleanup**: Free resources when done

### Algorithm Flow
```
get_next_line(fd):
├── Check for valid fd and BUFFER_SIZE
├── Read from file into buffer (if needed)
├── Append buffer to stored content
├── Find newline in content
├── Extract line (up to newline)
├── Update remaining content
└── Return line or NULL if EOF
```

### Helper Functions
- `ft_strjoin()`: Join strings safely
- `ft_strchr()`: Find characters in strings
- `ft_strdup()`: Duplicate strings
- `ft_substr()`: Extract substrings
- `ft_strlen()`: Get string length

---

## 🎮 Bonus Features

### Multiple File Descriptors
```c
// Handle multiple FDs simultaneously
#define MAX_FD 1024

// Static array for each FD
static char *saved[MAX_FD];

// Function works with any valid FD
char *get_next_line(int fd)
{
    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    // Implementation...
}
```

### Bonus Requirements
- [ ] Support for multiple file descriptors
- [ ] No global variables (only static in function)
- [ ] Memory leak free
- [ ] Proper error handling
- [ ] Norminette compliant

### Testing Bonus
```bash
# Test multiple FDs
make test_bonus

# Test with different buffer sizes
BUFFER_SIZE=1 make test
BUFFER_SIZE=1000000 make test
```

---

## 🧪 Testing

### Test Suite
```bash
# Run basic tests
make test

# Test with different buffer sizes
BUFFER_SIZE=1 ./test
BUFFER_SIZE=42 ./test
BUFFER_SIZE=9999 ./test

# Test edge cases
make test_edge_cases

# Memory leak testing
make test_leaks
```

### Test Files
- **Basic files**: Simple text files with various line endings
- **Edge cases**: Empty files, single line, no newline at end
- **Large files**: Performance testing with big files
- **Binary files**: Ensure proper text handling
- **Invalid FDs**: Error handling for bad file descriptors

### Sample Test Output
```
Testing basic functionality...
✓ Empty file: NULL
✓ Single line: "Hello World\n"
✓ Multiple lines: Correct line separation
✓ No final newline: Proper handling

Testing buffer sizes...
✓ BUFFER_SIZE=1: Works correctly
✓ BUFFER_SIZE=42: Standard behavior
✓ BUFFER_SIZE=1000: Performance maintained

Testing error cases...
✓ Invalid fd: Returns NULL
✓ Closed fd: Returns NULL
✓ BUFFER_SIZE <= 0: Returns NULL
```

---

## 📁 Project Structure

```
get_next_line/
├── Makefile                    # Build configuration
├── get_next_line.c            # Main function
├── get_next_line.h            # Header file
├── get_next_line_utils.c      # Helper functions
├── get_next_line_bonus.c      # Bonus version
├── get_next_line_bonus.h      # Bonus header
├── main.c                     # Test program
├── test_files/                # Test input files
│   ├── empty.txt
│   ├── single_line.txt
│   ├── multiple_lines.txt
│   └── large_file.txt
└── README.md                  # This file
```

---

## ⚙️ Configuration

### BUFFER_SIZE
```c
// Define buffer size (compile-time)
#define BUFFER_SIZE 42

// Can be overridden at compile time
gcc -D BUFFER_SIZE=1024 get_next_line.c
```

### Makefile Variables
```makefile
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

# Source files
SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils.c

# Targets
all: $(NAME)
bonus: $(BONUS_NAME)
```

### Performance Tuning
- **Small BUFFER_SIZE**: More system calls, slower but memory efficient
- **Large BUFFER_SIZE**: Fewer system calls, faster but more memory usage
- **Optimal**: Usually 32-128 bytes for balance

---

## 🤝 Contributing

<div align="center">

**42 School Project - Perfect for peer evaluation!**

- 📝 **Code Reviews**: Share your GNL implementation
- 🐛 **Bug Fixes**: Handle edge cases and improve robustness
- ⚡ **Optimizations**: Improve performance and memory usage
- 🧪 **Test Cases**: Add comprehensive test scenarios
- 📚 **Documentation**: Improve code comments and examples

</div>

---

## 🙏 Acknowledgments

<div align="center">

**Thanks to:**

- **42 School** for the challenging file I/O project
- **Peer evaluators** for thorough code reviews
- **C Standard Library** for file handling inspiration

---

**Built with ❤️ at 42 School**

[![42 Get_Next_Line](https://img.shields.io/badge/42-Get_Next_Line-000000?style=for-the-badge&logo=42&logoColor=white)](#)

</div>