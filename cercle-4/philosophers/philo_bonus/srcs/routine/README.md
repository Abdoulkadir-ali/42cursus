# Routine Module (Philo Bonus)

Implements the main simulation routines for philosophers using processes and semaphores. This module coordinates eating, sleeping, thinking, death detection, and meal completion, with precise control over concurrency and resource management.

---

## 📂 Directory Structure
- `death.c` — Death detection monitor for each philosopher process
- `eat.c` — Fork acquisition, eating, meal tracking, and meal completion monitor
- `routine.c` — Simulation setup, process management, and main philosopher routine
- `sleep.c` — Sleeping action for philosophers
- `think.c` — Thinking action and timing adjustment for philosophers

---

## 🏗️ **Global Pipeline**

1. `philo()` (routine.c) initializes semaphores and launches philosopher processes.
2. `start_simulation()` forks one process per philosopher, each running `philo_routine()`.
3. Each philosopher process:
   - Initializes its meal_lock semaphore
   - Starts a `death_monitor` thread to detect starvation
   - Alternates between `philo_eat`, `philo_sleep`, and `philo_think` in an infinite loop
4. `philo_eat()` (eat.c) acquires forks via semaphores, updates meal count, signals meal completion, and releases forks.
5. `meal_monitor()` (eat.c) runs in a thread to detect when all philosophers have finished their required meals, signaling simulation stop.
6. `death_monitor()` (death.c) checks for starvation and signals simulation stop if a philosopher dies.
7. `philo_sleep()` (sleep.c) and `philo_think()` (think.c) print status and manage timing, with `philo_think` adjusting for odd philosopher counts.
8. `terminate_simulation()` (routine.c) kills all philosopher processes and cleans up semaphores.

---

## 🔬 **Detailed Function Flow**

### `routine.c`
- `init_semaphores`: Unlinks and opens all semaphores for forks, print, stop, meal_check, and waiter.
- `start_simulation`: Forks philosopher processes, each running `philo_routine`.
- `philo_routine`: Initializes meal_lock, starts `death_monitor`, and loops through eating, sleeping, and thinking.
- `philo`: Sets up simulation, launches meal monitor if needed, waits for stop, and terminates.
- `terminate_simulation`: Kills all processes, waits for them, closes and unlinks semaphores.

### `eat.c`
- `philo_eat`: Handles fork acquisition, eating, meal tracking, and fork release. Signals meal completion if needed.
- `take_forks`/`drop_forks`: Manage fork and waiter semaphores for deadlock avoidance.
- `handle_one_philo`: Special routine for single philosopher edge case.
- `meal_monitor`: Waits for meal_check signals from all philosophers, then signals stop.

### `death.c`
- `death_monitor`: Monitors each philosopher for starvation, signals stop and exits if death occurs.

### `sleep.c`
- `philo_sleep`: Prints sleeping status and sleeps for the configured time.

### `think.c`
- `philo_think`: Prints thinking status and adjusts timing for odd philosopher counts.

---

## 🛠️ **Developer Notes**
- All routines use semaphores for process-safe synchronization.
- Deadlock avoidance is handled by the waiter semaphore in `eat.c`.
- Meal completion and death detection are signaled via semaphores to the main process.
- Edge cases (single philosopher, odd/even counts) are handled explicitly in routines.
- For detailed function documentation, see docblocks in each source file.

---

This README provides a precise, code-aligned overview of the philo_bonus routine module and its real control flow.
