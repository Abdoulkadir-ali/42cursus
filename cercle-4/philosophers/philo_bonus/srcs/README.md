# 🧭 **Source Pipeline (Bonus)** - *How the simulation moves from startup to routines*

> **A high-level map of the `srcs/` tree.**  
> This README explains how the source folders fit together in the global philosophers bonus pipeline, from argument parsing and setup to routines and simulation control.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-srcs%2F-overview-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-pipeline-success?style=for-the-badge)

---

## 📖 **Overview**

The `srcs/` directory is the operational heart of the bonus project. It contains the runtime code that turns simulation parameters into a working philosopher pipeline with bonus features:

1. parse and validate arguments
2. initialize simulation rules and resources
3. create philosopher processes/threads
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

The full runtime pipeline across `srcs/` is:

1. `core/` starts the simulation through `main` and argument parsing.
2. `core/parse.c` validates and fills the rules struct.
3. `routine/` sets up semaphores, philosopher data, processes/threads, and monitor.
4. Each philosopher process/thread runs its routine (eat, sleep, think, check death).
5. `routine/death.c` and monitor detect death and meal completion.
6. `lib/` provides helpers for string conversion, printing, and timing.

---

## 🗂️ **Top-Level Folders**

### `core/`
- Starts the program and validates arguments.
- Owns simulation setup and launch.
- Bridges argument parsing and routine startup.

### `routine/`
- Implements routines for philosopher actions.
- Handles eating, sleeping, thinking, and death detection.
- Manages process/thread creation, joining, and synchronization.

### `lib/`
- Hosts project-local helpers for string conversion, printing, and timing.
- Provides supporting infrastructure for argument parsing and status output.

---

## 🔄 **Typical Simulation Journey**

For a normal simulation, the trip through `srcs/` looks like this:

1. `core/main.c` starts the simulation and parses arguments.
2. `core/parse.c` fills the rules struct.
3. `routine/routine.c` sets up processes/threads and launches the main loop.
4. Each philosopher process/thread runs its routine (eat, sleep, think, check death).
5. `routine/death.c` and monitor detect death and meal completion.
6. `lib/` functions support argument conversion, printing, and timing.
7. Simulation ends and resources are cleaned up.

---

## 🧩 **How the Folders Depend on Each Other**

- `core/` depends on `routine/` and `lib/` directly.
- `routine/` depends on `lib/` for printing and timing.
- `lib/` provides low-level helpers used throughout the simulation.

This is why the tree feels linear, but actually coordinates multiple processes/threads and shared resources:

```text
startup -> parse -> setup -> routines -> monitor -> cleanup
```

---

This README matches the structure and style of EXAMPLE.md, tailored for the philosophers bonus srcs module.
