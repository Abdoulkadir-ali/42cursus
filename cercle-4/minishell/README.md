# 🐚 **Minishell** - *As beautiful as a shell*

> **A minimal bash-like shell implementation.**  
> Recreating the core functionality of a Unix shell in C.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-In%20Progress-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**Minishell** is a 42 school project that involves creating a simplified shell. The goal is to understand how a shell works under the hood: process creation, synchronization, file file descriptors, pipes, redirections, and signal handling.

---

## ✨ **Features**

### 🧠 **Parsing & Expansion**
- **Robust Tokenizer**: Handles complex command structures.
- **Quote Handling**: Supports single (`'`) and double (`"`) quotes.
  - Double quotes expand variables (`$USER`).
  - Single quotes preserve literal values.
- **Environment Variables**: Expands `$VAR` and `$?` (exit status).

### ⚙️ **Execution**
- **Pipelines**: Connects commands via pipes (`|`).
- **Redirections**:
  - Input (`<`)
  - Output (`>`)
  - Append (`>>`)
  - Heredoc (`<<`) *(In Progress)*
- **Path Resolution**: Finds executables using the `PATH` environment variable.

### 🛠 **Built-in Commands**
- `echo` (with `-n` option)
- `cd` (with relative or absolute paths)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### 🚦 **Signals**
- `Ctrl-C`: Interrupts current process, displays new prompt.
- `Ctrl-D`: Exits the shell (EOF).
- `Ctrl-\`: Quits execution (does nothing in prompt).

---

## 🚀 **Getting Started**

### **Prerequisites**
- **GCC** compiler
- **Make**
- **Readline** library

### **Installation**

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Run the shell:**
   ```bash
   ./minishell
   ```

---

## 🎮 **Usage Examples**

```bash
# Simple commands
minishell> ls -la
minishell> pwd

# Pipes
minishell> ls | grep "Make" | wc -l

# Redirections
minishell> echo "Hello World" > out.txt
minishell> cat < out.txt

# Environment Variables
minishell> echo $USER
minishell> export FOO=bar
minishell> echo $FOO
```

---

## 🏗 **Architecture**

1. **Lexer/Tokenizer**: Breaks input string into tokens (Words, Pipes, Redirections).
2. **Parser/AST Builder**: Constructs an Abstract Syntax Tree (AST) from tokens.
3. **Expander**: Processes quotes and environment variables.
4. **Executor**: Traverses the AST to execute commands, managing forks and pipes.

---

## 👥 **Authors**

- **Abdoali** - [Profile](https://github.com/)

---
