# Pipex

Pipex is a C program that recreates the behavior of shell pipes (`|`) in Unix-like systems. It takes an input file, executes a series of commands where the output of each command is piped as input to the next command, and writes the final output to an output file.

This project is part of the 42 School curriculum (Circle 3).

## Features

- **Standard Mode**: Execute multiple commands with piping
- **Here Document Mode**: Support for here document input (bonus feature)
- **Error Handling**: Proper error management and cleanup
- **Memory Management**: No memory leaks
- **Custom Libraries**: Uses custom implementations of libft and get_next_line

## Building the Project

### Prerequisites

- GCC compiler
- Make

### Compilation

1. Clone or navigate to the project directory
2. Run the following command to build the executable:

```bash
make
```

This will compile the main program along with the required libraries (libft and gnl).

### Cleaning

- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Rebuild the entire project

## Usage

### Standard Mode

```bash
./pipex infile "cmd1" "cmd2" ... outfile
```

**Example:**
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

This is equivalent to: `< input.txt grep hello | wc -l > output.txt`

### Here Document Mode (Bonus)

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" ... outfile
```

**Example:**
```bash
./pipex here_doc EOF "grep hello" "wc -l" output.txt
```

This allows you to provide input directly in the terminal until the LIMITER string is entered.

## Project Structure

```
pipex/
├── Makefile                    # Main build file
├── includes/
│   └── pipex.h                # Header file with function declarations
├── srcs/
│   ├── pipex/                 # Main source files
│   │   ├── main.c            # Program entry point
│   │   ├── pipex.c           # Core pipex logic
│   │   ├── process.c         # Process management
│   │   ├── pipes.c           # Pipe creation and management
│   │   ├── parser.c          # Command parsing
│   │   ├── cmd.c             # Command execution
│   │   ├── io.c              # Input/Output handling
│   │   ├── access.c          # File access checking
│   │   ├── exit.c            # Error handling and cleanup
│   │   └── here_doc.c        # Here document implementation
│   ├── libft/                # Custom C standard library functions
│   └── gnl/                  # Get Next Line implementation
└── README.md                 # This file
```

## Implementation Details

- **Process Management**: Uses `fork()` to create child processes for each command
- **Pipe Communication**: Implements inter-process communication using Unix pipes
- **File Redirection**: Handles input/output file redirection using `dup2()`
- **Path Resolution**: Searches for executable commands in PATH environment variable
- **Memory Safety**: Proper allocation and deallocation of resources

## Error Handling

The program handles various error conditions:
- Invalid number of arguments
- File access permissions
- Command not found
- Pipe creation failures
- Memory allocation errors

## Dependencies

- **Libft**: Custom implementation of standard C library functions
- **Get Next Line**: Custom implementation for reading lines from file descriptors

## Testing

You can test the program with various commands and compare its output with the equivalent shell commands.

**Example test:**
```bash
# Create test input
echo -e "hello world\nhello universe\nbye world" > test_input.txt

# Test with pipex
./pipex test_input.txt "grep hello" "wc -l" pipex_output.txt

# Compare with shell
< test_input.txt grep hello | wc -l > shell_output.txt

# Check if outputs match
diff pipex_output.txt shell_output.txt
```

## Author

[Your Name] - 42 Student

## License

This project is part of the 42 School curriculum and follows their licensing terms.