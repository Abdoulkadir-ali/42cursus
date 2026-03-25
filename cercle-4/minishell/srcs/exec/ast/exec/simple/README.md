# 🔬 Simple Command Executor (`srcs/exec/ast/exec/simple`)

![Domain](https://img.shields.io/badge/Domain-Terminal_Command_Leaves-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Drives AST terminal leaves representing literal user commands (like `ls` or `echo`). Forms the fundamental transition point comparing the finalized `char **args` payload against the internal `builtins/` matrix or forcing an OS-level `execve()` spawn for physical binaries.

---

## ⚙️ Core Mechanic & Algorithms
**The Fork & Dispatch Matrix (`exec_simple_command`):**
1. Collects raw AST tokens (`args` and prefix `assigns`).
2. Calls `expand_tokens()` recursively to translate macros (`$VAR`, `*` wildcards) into an aggregated C-based arrays (`char **`).
3. Applies temporary variables (like `VAR=1`) via environment cloning locally for the next step.
4. If `is_builtin()` is true: 
   - Invokes `exec_builtin()`. Runs sequentially in memory.
5. If false:
   - Triggers `child_execution()` within an orchestrated OS `fork()`.
   - Modifies `_` env wrapper. Finds explicit PATH. Calls `execve()`.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Fallback Underscore (`_`) Assignment:** Every time an external binary is spawned, the physical shell environment MUST mutate `_=/path/to/binary`. `child_execution()` guarantees this mutation occurs immediately prior to `execve()`. 

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Binary Not Found in `$PATH`** | `find_path()` fails to return target. | Child calls `exit(127)` mimicking `command not found`. |
| **Binary Found but unexecutable (`chmod -x`)** | `execve()` falls via OS `EACCES`. | Child calls `exit(126)` mimicking `Permission denied`. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Signal Insulation:** A `fork()`'d child processing an external binary resets signal dispositions (e.g. `SIGINT` maps back to `SIG_DFL`). The parent Minishell explicitly `SIG_IGN`s these interrupts temporarily while waiting, ensuring the parent is insulated from Ctrl+C commands intended strictly for the running binary (`cat`).

---

## 🔌 API Signatures
```c
/**
 * @brief Orchestrates a raw AST Command node against builtins or `execve`.
 * @param node `TOKEN_WORD` AST wrapper.
 * @param state Active runtime environment tracking exits.
 * @return `0` on success, or physical mapped failure codes (`127`, `1`).
 */
int	exec_simple_command(t_ast *node, t_shell_state *state);
```
