# 🧭 **Philo Module Pipeline**

> **A high-level map of the `philo/` tree.**  
> This README explains how the folders fit together in the global philosophers pipeline, from argument parsing and setup to thread routines and simulation control.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-philo%2F-overview-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-pipeline-success?style=for-the-badge)

---

## 📖 **Overview**

The `philo/` directory is the operational heart of the project. It contains the runtime code that turns simulation parameters into a working philosopher pipeline:

1. parse and validate arguments
2. initialize simulation rules and resources
3. create philosopher threads
4. run the main simulation loop
5. coordinate eating, sleeping, thinking, and death detection
6. print status updates and manage timing
7. clean up resources and exit

At a high level, the simulation behaves like this:

```text
core -> routine -> lib
```

`lib/` provides shared utility code for argument parsing, printing, and timing.

---

## 🚀 **Global Pipeline**

The full runtime pipeline across `philo/` is:

1. `srcs/core/` starts the simulation through `main` and argument parsing.
2. `srcs/core/parse.c` validates and fills the rules struct.
3. `srcs/routine/` sets up mutexes, philosopher data, threads, and monitor.
4. Each philosopher thread runs its routine (eat, sleep, think, check death).
5. `srcs/routine/death.c` and monitor thread detect death and meal completion.
6. `srcs/lib/` provides helpers for string conversion, printing, and timing.

---

## 🗂️ **Top-Level Folders**

### `includes/`
- Project-wide types and function prototypes.

### `srcs/core/`
- Starts the program and validates arguments.
- Owns simulation setup and launch.
- Bridges argument parsing and thread routine startup.

### `srcs/routine/`
- Implements thread routines for philosopher actions.
- Handles eating, sleeping, thinking, and death detection.
- Manages thread creation, joining, and synchronization.

### `srcs/lib/`
- Hosts project-local helpers for string conversion, printing, and timing.
- Provides supporting infrastructure for argument parsing and status output.

---

## 🔄 **Typical Simulation Journey**

For a normal simulation, the trip through `philo/` looks like this:

1. `srcs/core/main.c` starts the simulation and parses arguments.
2. `srcs/core/parse.c` fills the rules struct.
3. `srcs/routine/routine.c` sets up threads and launches the main loop.
4. Each philosopher thread runs its routine (eat, sleep, think, check death).
5. `srcs/routine/death.c` and monitor thread detect death and meal completion.
6. `srcs/lib/` functions support argument conversion, printing, and timing.
7. Simulation ends and resources are cleaned up.

---

## 🧩 **How the Folders Depend on Each Other**

- `srcs/core/` depends on `srcs/routine/` and `srcs/lib/` directly.
- `srcs/routine/` depends on `srcs/lib/` for printing and timing.
- `srcs/lib/` provides low-level helpers used throughout the simulation.

This is why the tree feels linear, but actually coordinates multiple threads and shared resources:

```text
startup -> parse -> setup -> thread routines -> monitor -> cleanup
```

---

This README matches the structure and style of EXAMPLE.md, tailored for the philosophers project philo module.