# Lib Module (Philo Bonus)

Provides utility functions for string conversion, printing, and timing. These helpers are used throughout the bonus simulation for argument parsing, status output, and precise time management.

---

## 📂 Directory Structure
- `srcs/lib/` — Utility function root
  - `ft_atoll.c` — String to integer conversion
  - `ft_putstr_fd.c` — String output to file descriptor
  - `ft_strlen.c` — String length calculation
  - `print.c` — Thread/process-safe status printing
  - `time.c` — Time measurement and precise sleeping

---

## 🏗️ How It Works

### Global Pipeline
- Utility functions are called from core and routine modules to:
  - Convert arguments (`ft_atoll`)
  - Print errors and status messages (`ft_putstr_fd`, `print_status`)
  - Measure elapsed time and sleep accurately (`now`, `precise_usleep`)

### `ft_atoll.c`
- Converts a string to a long long integer.
- Used for parsing numeric arguments from input.

### `ft_putstr_fd.c`
- Writes a string to a given file descriptor.
- Used for error messages and status output.

### `ft_strlen.c`
- Calculates the length of a string.
- Used by printing functions and argument validation.

### `print.c`
- Provides `print_status` for thread/process-safe status output.
- Uses `ft_putnbr` for printing numbers and `ft_putstr_fd` for messages.
- Locks the appropriate mutex/semaphore to ensure output consistency.

### `time.c`
- Provides `now` for current time in milliseconds.
- Provides `precise_usleep` for accurate sleeping intervals.
- Used for timing philosopher actions and simulation events.

---

## 🛠️ Developer Notes
- All functions are designed for thread/process safety and minimal dependencies.
- Printing and timing utilities are critical for simulation correctness and output clarity.
- For detailed function documentation, see docblocks in the source files and header definitions.

This README matches the structure and style of the core module, tailored for the philosophers bonus project lib module.
