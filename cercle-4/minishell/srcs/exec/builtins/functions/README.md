# 🔬 Builtins Functions Subpackage (`srcs/exec/builtins/functions`)

![Domain](https://img.shields.io/badge/Domain-Internal_Command_Logic-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Houses the literal C-implementations for the 7 primary Bash internal commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`. These functions meticulously reconstruct the physical output patterns, option-flag handlers (`-n`), and POSIX edge-cases exhibited by naked GNU coreutils.

---

## ⚙️ Core Mechanic & Algorithms
**Distinct Sub-Implementations:**
1. **`echo.c`:** Actively scans for sequential `-n` / `-nnn` flags. Suppresses terminating `\n` if present.
2. **`env.c`:** Iterates `state->envp`, strictly masking any variables that do not possess an active `=`.
3. **`pwd.c`:** Attempts `getcwd()` initially. If the kernel OS mapping fails, inherently falls back to reading the `$PWD` shell state variable.
4. **`exit.c`:** Parses the requested exit status via `ft_safe_atoll()`. Validates that arguments are purely numeric. Prints `exit` directly to STDERR natively on TTY connections.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Export Sorting:** Running `export` natively with zero parameters triggers a completely disparate pipeline. The shell MUST print the active environment array sorted lexicographically, preceded by `declare -x `. Found in `export.c` -> `handle_export_no_args`.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`exit` provided with Non-Numeric argument** | Prints `numeric argument required`. | Shell terminates completely with OS status `2`. |
| **`exit` provided with `>1` Arguments** | Prints `too many arguments`. | Command cancels. Returns `1`. Shell `exit` DOES NOT trigger. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Builtin Error Formatting:** When builtins fail, the error is NOT thrown using standard `perror()`. Because we must match Bash syntax perfectly, errors are hard-baked using `ft_puterror()` specifying `minishell: [BUILTIN]: [MSG]`.

---

## 🔌 API Signatures
```c
/**
 * @brief Universal signature for all builtin functions registered in `init.c`.
 * @param args NULL-terminated `char **argv` matrix from the AST command.
 * @param state Immutable or mutable shell context (e.g., envp tracking).
 * @return `0` on success. `1`-`255` on failure, piped directly to `exit_code`.
 */
int	ft_builtin_name(char **args, t_shell_state *state);
```
