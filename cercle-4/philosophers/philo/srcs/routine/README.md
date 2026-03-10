# Routine Module (Philosophers)

Implements the main thread routines for philosopher actions, including eating, sleeping, thinking, and death detection. This subsystem coordinates thread creation, synchronization, and the simulation loop.

---

## 📂 Directory Structure
- `srcs/routine/` — Thread routine root
  - `death.c` — Death detection and meal completion
  - `eat.c` — Fork acquisition, eating, and meal tracking
  - `helper.c` — Mutex and thread setup/teardown helpers
  - `routine.c` — Simulation entry, thread creation, and main loop
  - `sleep.c` — Sleeping and thinking actions
  - `think.c` — Thinking action (status output)

---

## 🏗️ How It Works

### Global Pipeline
1. Simulation starts in `philo()` (routine.c), which sets up mutexes, philosopher data, threads, and monitor.
2. Each philosopher thread runs `philo_routine()` (routine.c), looping through eat, sleep, think, and death checks.
3. `philo_eat()` (eat.c) handles fork acquisition, eating, and meal count updates.
4. `philo_sleep()` and `philo_think()` (sleep.c, think.c) update status and manage timing.
5. `monitor_routine()` (routine.c) checks for philosopher death and meal completion using helpers from `death.c`.
6. Helper functions in `helper.c` manage mutex initialization, thread creation, joining, and destruction.

### `routine.c`
- Entry point for simulation setup and thread management.
- `philo()` initializes all resources and launches threads.
- `philo_routine()` is the main loop for each philosopher.

### `eat.c`
- Handles fork locking, eating, and meal count updates.
- Ensures proper synchronization and deadlock avoidance.

### `death.c`
- Implements death detection and meal completion checks.
- Used by monitor thread to end simulation when needed.

### `helper.c`
- Initializes and destroys mutexes.
- Creates philosopher threads and joins them after simulation.

### `sleep.c` & `think.c`
- Provide status updates and timing for sleep and think actions.

---

## 🛠️ Developer Notes
- All routines are thread-safe and use mutexes for synchronization.
- The simulation loop is robust to edge cases (single philosopher, invalid input).
- Entry points: `philo`, `philo_routine`, `philo_eat`, `monitor_routine`.
- For detailed function documentation, see docblocks in the source files and header definitions.

This README matches the structure and style of the core and lib modules, tailored for the philosophers project routine module.