# Core Module (Philo Bonus)

Handles simulation startup, argument parsing, and main control flow for the bonus project. This subsystem is responsible for validating input, initializing simulation rules, and launching philosopher processes.

---

## 📂 Directory Structure
- `main.c` — Program entry point, argument validation, and simulation launch
- `parse.c` — Argument parsing and rules setup

---

## 🏗️ **Detailed Pipeline**

### `main.c`
- Validates argument count (should be 5 or 6).
- Calls `parse_rules` to fill the rules struct with simulation parameters.
- Checks for maximum philosopher limit and prints errors to stderr.
- Launches the simulation with `philo(&rules)`.

#### Control Flow:
1. User runs the program with arguments.
2. `main` checks argument count and values.
3. If invalid, prints error and exits.
4. If valid, calls `parse_rules`.
5. If rules are valid, launches simulation via `philo(&rules)`.

### `parse.c`
- `parse_basic_args`: Converts string arguments to numbers, checks validity, and populates rules struct.
- `parse_meals`: Handles optional meal count argument, sets to -1 if not provided.
- `parse_rules`: Chains both parsing steps, returns 1 on any invalid input.

#### Control Flow:
1. `parse_basic_args` extracts and checks core parameters (number of philosophers, times).
2. `parse_meals` sets the meal count or disables it if not provided.
3. `parse_rules` returns 0 on success, 1 on any invalid input.

---

## 🛠️ **Developer Notes**
- All argument parsing is centralized in `parse.c` for clarity and maintainability.
- Error messages are printed to stderr for user visibility.
- Entry points: `main`, `parse_rules`.
- For detailed function documentation, see docblocks in the source files and header definitions.

---

This README provides a precise, code-aligned overview of the philo_bonus core module and its real control flow.
