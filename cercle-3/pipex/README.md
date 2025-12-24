# 🚀 Pipex - Unix Pipes Recreation

<div align="center">

![42 Badge](https://img.shields.io/badge/42-FF3131?style=for-the-badge&logo=42&logoColor=white)
![C Language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white)

**A powerful C program that recreates the magic of Unix shell pipes!**

[📖 Overview](#-overview) • [⚡ Features](#-features) • [🔧 Installation](#-installation) • [🎯 Usage](#-usage) • [🧪 Testing](#-testing) • [📁 Structure](#-project-structure)

</div>

---

## 📖 Overview

**Pipex** is an advanced C program that faithfully recreates the behavior of Unix shell pipes (`|`) in Unix-like systems. It takes an input file, executes a series of commands where each command's output becomes the input for the next, and writes the final result to an output file.

This project is part of the prestigious **42 School curriculum** (Circle 3) - a rigorous computer science program that emphasizes hands-on learning and deep understanding of system programming.

```bash
# Traditional shell piping
< input.txt grep "pattern" | wc -l > output.txt

# Pipex equivalent
./pipex input.txt "grep pattern" "wc -l" output.txt
```

---

## ⚡ Features

<div align="center">

| Feature | Description |
|---------|-------------|
| 🔄 **Standard Piping** | Execute multiple commands with seamless pipe connections |
| 📝 **Here Documents** | Interactive input mode with custom delimiters (bonus) |
| 🛡️ **Robust Error Handling** | Comprehensive error management and graceful failure recovery |
| 🧠 **Memory Safe** | Zero memory leaks with meticulous resource management |
| 📚 **Custom Libraries** | Built on custom libft and get_next_line implementations |
| ⚡ **High Performance** | Optimized process management and I/O operations |

</div>

### 🎯 Key Capabilities

- ✅ **Multi-command chaining** with unlimited pipe connections
- ✅ **File I/O redirection** with proper permission handling
- ✅ **PATH resolution** for executable discovery
- ✅ **Signal handling** and process synchronization
- ✅ **Cross-platform compatibility** (Unix-like systems)

---

## 🔧 Installation

### 📋 Prerequisites

- 🐧 **Linux/Unix environment**
- 🛠️ **GCC compiler** (or compatible C compiler)
- 📝 **GNU Make**

### 🚀 Quick Start

```bash
# 1. Clone the repository
git clone <your-repo-url>
cd pipex

# 2. Build the project
make

# 3. Verify installation
./pipex --help  # (if implemented) or check with a simple command
```

### 🧹 Build Targets

```bash
make          # Build the executable
make clean    # Remove object files
make fclean   # Remove all build artifacts
make re       # Rebuild from scratch
```

---

## 🎯 Usage

### 🔄 Standard Mode

Execute commands with pipe connections between them:

```bash
./pipex infile "command1" "command2" ... outfile
```

#### 💡 Practical Examples

```bash
# Count lines containing "error" in a log file
./pipex access.log "grep error" "wc -l" error_count.txt

# Process text: find words, sort, remove duplicates
./pipex words.txt "grep -E '^[a-z]+$' "sort" "uniq" clean_words.txt

# Complex data processing pipeline
./pipex data.csv "cut -d',' -f2" "sort -n" "head -10" top_values.txt
```

**Shell equivalent:** `< infile command1 | command2 | ... > outfile`

### 📝 Here Document Mode (Bonus)

Interactive input with custom delimiter:

```bash
./pipex here_doc DELIMITER "command1" "command2" ... outfile
```

#### 💡 Interactive Example

```bash
# Start here document mode
./pipex here_doc EOF "grep hello" "wc -l" output.txt

# Terminal input (type your content, end with EOF):
Hello World
Hello Universe
Goodbye World
EOF

# Result: output.txt contains "2"
```

---

## 🧪 Testing

### 🧪 Basic Functionality Test

```bash
# Create test data
echo -e "apple\nbanana\ncherry\napple\ndate" > fruits.txt

# Test with pipex
./pipex fruits.txt "grep apple" "wc -l" pipex_result.txt

# Compare with shell
< fruits.txt grep apple | wc -l > shell_result.txt

# Verify results match
diff pipex_result.txt shell_result.txt && echo "✅ Test passed!" || echo "❌ Test failed!"
```

### 🧪 Advanced Testing Suite

```bash
# Test multiple scenarios
./test_script.sh  # Create your own comprehensive test script

# Test edge cases
./pipex nonexistent.txt "cat" "wc" output.txt  # File not found
./pipex input.txt "invalid_cmd" "wc" output.txt  # Command not found
./pipex input.txt "cat" output.txt  # Single command
```

### 🧪 Performance Benchmarking

```bash
# Compare execution time
time < large_file.txt grep "pattern" | sort | uniq > shell_output.txt
time ./pipex large_file.txt "grep pattern" "sort" "uniq" pipex_output.txt

# Verify identical results
diff shell_output.txt pipex_output.txt
```

---

## 📁 Project Structure

```
🗂️ pipex/
├── 📄 Makefile                    # 🏗️  Build automation
├── 📁 includes/
│   └── 📄 pipex.h                # 🏷️  Function declarations & macros
├── 📁 srcs/
│   ├── 📁 pipex/                 # 🎯 Main program logic
│   │   ├── 📄 main.c            # 🚪 Program entry point
│   │   ├── 📄 pipex.c           # 🔧 Core pipeline logic
│   │   ├── 📄 process.c         # 👥 Process management
│   │   ├── 📄 pipes.c           # 🔗 Pipe creation & handling
│   │   ├── 📄 parser.c          # ✂️  Command parsing
│   │   ├── 📄 cmd.c             # ⚡ Command execution
│   │   ├── 📄 io.c              # 📥📤 I/O operations
│   │   ├── 📄 access.c          # 🔍 File access validation
│   │   ├── 📄 exit.c            # 🚨 Error handling & cleanup
│   │   └── 📄 here_doc.c        # 📝 Here document implementation
│   ├── 📁 libft/                # 📚 Custom C standard library
│   └── 📁 gnl/                  # 📖 Get Next Line utility
└── 📄 README.md                 # 📖 This documentation
```

---

## 🔍 Implementation Details

### 🏗️ Architecture

- **Process Management**: `fork()` system calls for parallel execution
- **Inter-Process Communication**: Unix pipes for data streaming
- **File Redirection**: `dup2()` for stdin/stdout manipulation
- **Path Resolution**: Environment variable parsing for executable location
- **Memory Management**: Custom allocation with leak prevention

### 🛡️ Error Handling Strategy

The program gracefully handles numerous error scenarios:

- ❌ **Argument validation** - Incorrect parameter count
- 📁 **File permissions** - Access denied scenarios
- 🔍 **Command resolution** - Executable not found in PATH
- 🔧 **System calls** - Pipe creation and process spawning failures
- 💾 **Memory allocation** - Out-of-memory conditions

### 📚 Dependencies

| Library | Purpose | Location |
|---------|---------|----------|
| **Libft** | Custom C standard functions | `srcs/libft/` |
| **GNL** | Line-based file reading | `srcs/gnl/` |
| **System Headers** | Unix system calls | `<unistd.h>`, `<fcntl.h>`, etc. |

---

## 🤝 Contributing

<div align="center">

**Found a bug? Have a suggestion?**

🐛 [Report Issues](https://github.com/yourusername/pipex/issues) • 💡 [Submit Ideas](https://github.com/yourusername/pipex/discussions)

</div>

### 🧑‍💻 Development Setup

```bash
# Fork and clone
git clone https://github.com/yourusername/pipex.git
cd pipex

# Create feature branch
git checkout -b feature/amazing-improvement

# Make changes, test thoroughly
make && ./test_suite.sh

# Submit pull request
git push origin feature/amazing-improvement
```

---

## 📊 Project Stats

<div align="center">

![GitHub repo size](https://img.shields.io/github/repo-size/yourusername/pipex?style=flat-square)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/yourusername/pipex?style=flat-square)
![GitHub language count](https://img.shields.io/github/languages/count/yourusername/pipex?style=flat-square)
![GitHub last commit](https://img.shields.io/github/last-commit/yourusername/pipex?style=flat-square)

</div>

---

## 🙏 Acknowledgments

<div align="center">

**Special thanks to:**

- 🏫 **42 School** for the challenging curriculum
- 👨‍🏫 **Project mentors** for guidance and feedback
- 🌐 **Open source community** for inspiration and tools

</div>

---

## 📜 License

<div align="center">

**This project is part of the 42 School curriculum and follows their licensing terms.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

---

<div align="center">

**Made with ❤️ by [Your Name] - 42 Student**

⭐ **Star this repo if you found it helpful!**

[⬆️ Back to Top](#-pipex---unix-pipes-recreation)

</div>