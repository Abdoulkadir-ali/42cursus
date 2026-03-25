# 🔬 Signals Management Subpackage (`srcs/state/signals`)

![Domain](https://img.shields.io/badge/Domain-Kernel_Signals-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Strictly manages the process configuration for `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\), and `SIGTERM` (pkill) across branching context modes. Dictates global state mutation through `g_last_signal` and provides hook intervention into the GNU `readline` infinite loop.

---

## ⚙️ Core Mechanic & Algorithms
**The Context Mode Matrix:**
1. **`SIGNAL_INTERACTIVE`:** Bound during the main prompt. `SIGINT` writes `\n` and forces `readline` to redisplay an empty buffer. `rl_event_hook` is bound to `event_hook` to poll for `SIGTERM`. `SIGQUIT` is strictly ignored.
2. **`SIGNAL_HEREDOC`:** Bound during heredoc reading. `SIGINT` simply breaks the line and records `130` in the global variable so the caller aborts the heredoc sequence.
3. **`SIGNAL_BLOCKING`:** Bound when waiting on execution (`sys/wait`). `SIGINT` is ignored by the shell parent (the child process will receive the signal natively).
4. **`SIGNAL_NON_INTERACTIVE`:** Bound for stdin pipes or scripts. Inherits default OS signals but explicitly traps `SIGTERM`.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **`SIGQUIT` Suppression:** Unlike naked processes, interactive shells must completely ignore `SIGQUIT` core dumps. We enforce this via `sa.sa_handler = SIG_IGN`.

> [!CAUTION]
> **`SIGINT` Readline Reset:** `Ctrl+C` in a prompt must not exit the shell. `handle_interactive` enforces `rl_replace_line("", 0)` and `rl_redisplay()` simulating proper Bash prompt flushing.

---

## 🚨 Error & Signal Propagation
| Signal Trigger (\`g_last_signal\`) | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`SIGTERM` received** | `handle_sigterm` assigns `g_last_signal = 15`. | `readline` hits `event_hook()`, triggers `rl_done = 1`. `minishell.c` notices `15`, frees line, and cleanly exits REPL. |
| **`SIGINT` during `interactive`** | Assigns `g_last_signal = 130`, flushes readline. | User presented with a fresh empty prompt on a new line. |
| **`SIGINT` during `heredoc`** | Assigns `g_last_signal = 130`, writes literal `\n`. | Heredoc loop detects global mutation, cancels pending file creation, triggers upstream abort. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Cross-Process Hook Safety:** Signal handlers can cause concurrent memory corruption. The only code executed inside our handlers are `write()` (async-signal-safe) or `readline` volatile mutations. The shell explicitly does *not* call `exit()` from inside handlers, relying instead on polling `g_last_signal`.

> [!NOTE]
> **The `pkill` Paradox (`SIGTERM`):** If an external process sends `SIGTERM`, `readline` normally hangs waiting for user input. We fix this by deliberately mapping `rl_event_hook = event_hook_function` which evaluates globals every 100ms cycle native to the readline library.

---

## 🔌 API Signatures
```c
/**
 * @brief Initialize signals for an executed child process.
 * Forces SIGINT, SIGQUIT, and SIGTERM back to SIG_DFL before execve.
 */
void	setup_child_signals(void);

/**
 * @brief Alter the shell's parent signal disposition.
 * @param mode Must be one of `SIGNAL_INTERACTIVE`, `SIGNAL_BLOCKING`, `SIGNAL_HEREDOC`, or `SIGNAL_NON_INTERACTIVE`.
 */
void	setup_signals(int mode);
```