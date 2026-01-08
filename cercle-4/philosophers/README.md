# 🍝 **Philosophers** - *I eat, therefore I sleep*

> **A Simulation of the Classic Dining Philosophers Problem**
> Master concurrent programming, threading, and mutex synchronization in C.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Concurrency](https://img.shields.io/badge/Concurrency-Threads%20%26%20Mutexes-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Stable-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**Philosophers** is a simulation based on the famous Dijkstra's dining philosophers problem. It explores the challenges of avoiding deadlock and resource starvation in a concurrent environment. This project creates a simulation where multiple threads (philosophers) sit at a round table, alternating between eating, sleeping, and thinking, while competing for a limited number of forks (mutexes).

The goal is to ensure no philosopher starves while preventing deadlocks and race conditions using mutexes and careful time management.

---

## ✨ **Key Features**

| Feature | Description |
| :--- | :--- |
| **🧵 Multi-threading** | Each philosopher runs as a separate thread, operating independently. |
| **🔒 Mutex Synchronization** | Forks are protected by mutexes to prevent data races and ensure exclusive access. |
| **⏱️ High-Precision Timing** | Custom timing functions ensure events happen with millisecond precision. |
| **👁️ Death Monitoring** | A supervisor system checks if any philosopher has died of starvation. |
| **🛡️ Deadlock Prevention** | Implemented logic to prevent circular wait conditions and resource deadlocks. |
| **🍽️ Resource Management** | Strict rules for fork acquisition and release to maintain simulation stability. |

---

## 🎮 **Usage**

Run the simulation by passing the required arguments to the executable.

### **Command Line Arguments**
`./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]`

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers and also the number of forks. |
| `time_to_die` | Time (in ms) a philosopher can go without eating before dying. |
| `time_to_eat` | Time (in ms) it takes for a philosopher to eat. |
| `time_to_sleep` | Time (in ms) a philosopher spends sleeping. |
| `[number_of_times_each_philosopher_must_eat]` | (Optional) Simulation stops if all philosophers eat at least this many times. |

### **Example**
```bash
# 5 philosophers, die in 800ms, eat in 200ms, sleep in 200ms
./philo 5 800 200 200
```

---

## 🛠️ **Installation**

Get **Philosophers** running on your Linux machine.

### **Prerequisites**
- **GCC / Clang** compiler
- **Make**
- **Pthread** library (usually included in standard C libraries on Linux)

### **Build Instructions**

```bash
# 1. Clone the repository
git clone https://github.com/Abdoulkadir-ali/42cursus
cd cercle-4/philosophers/philo

# 2. Compile the project
make

# 3. Run the simulation
./philo 4 410 200 200
```
