# Core Module (Philosophers)

Handles simulation startup, argument parsing, and main control flow. This subsystem is responsible for initializing the simulation rules, validating input, and launching the philosopher threads.

---

## 📂 Directory Structure
- `srcs/core/` — Core logic root
  - `main.c` — Program entry point, simulation initialization
  - `parse.c` — Argument parsing and rules setup

---

## 🏗️ How It Works

### Global Pipeline
1. The process enters the program through `main` in `main.c`.
2. `main` validates argument count and values, then calls `parse_rules`.
3. `parse_rules` (in `parse.c`) parses and validates simulation parameters, populating the `t_rules` struct.
4. If validation passes, `main` calls `philo(&rules)` to launch the simulation.
5. The simulation setup and thread management are handled in the next module (not shown here).

### `main.c`
- Contains only the executable entry point.
- Validates argument count (should be 5 or 6).
- Calls `parse_rules` to fill the rules struct.
- Checks for maximum philosopher limit.
- Launches the simulation with `philo(&rules)`.

### `parse.c`
- Owns argument parsing and validation.
- `parse_basic_args` extracts and checks core parameters (number of philosophers, times).
- `parse_meals` handles the optional meal count argument.
- `parse_rules` chains both parsing steps and returns error if any fail.

#### Pipeline Inside `parse.c`
1. `parse_basic_args` converts string arguments to numbers and checks validity.
2. `parse_meals` sets the meal count or disables it if not provided.
3. `parse_rules` returns 0 on success, 1 on any invalid input.

---

## 🛠️ Developer Notes
- The core module is intentionally thin: it owns startup, argument validation, and simulation launch.
- All argument parsing is centralized in `parse.c` for clarity and maintainability.
- Entry points: `main`, `parse_rules`.
- For detailed function documentation, see docblocks in the source files and header definitions.

This README matches the structure and style of EXAMPLE.md, tailored for the philosophers project core module.