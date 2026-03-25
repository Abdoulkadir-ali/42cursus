# 🔬 Redirection Controller Subpackage (`srcs/exec/ast/exec/redirection`)

![Domain](https://img.shields.io/badge/Domain-FD_Substitution-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Owns the physical logic of redirecting `STDIN`/`STDOUT` (`<`, `>`, `>>`) toward expanded filename targets. It dynamically hooks file descriptors natively within the current process context to ensure wrapped sub-ASTs inherit the exact I/O streams they require.

---

## ⚙️ Core Mechanic & Algorithms
**The Descriptor Substitution Engine (`perform_redirection_and_exec`):**
1. AST Node invokes the engine. The target filename is sent through parsing-level expansion.
2. If expansion guarantees a singular target (no ambiguous wildcards), `open_redirection_file()` attempts to `open()` the file based on the node's type (e.g. `O_TRUNC` vs `O_APPEND`).
3. Determines target FD (`STDOUT_FILENO` vs `STDIN_FILENO`).
4. **The Swap:** Uses `dup()` to secretly save the original console I/O stream into a backup integer. Uses `dup2()` to overwrite `STDOUT/STDIN` with the file's FD.
5. Recurses `exec_tree()` down into the wrapped subtree node so it runs fully redirected.
6. **The Unwind:** Closes the file, and restores the original console stream via `dup2()` using the backup integer.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Ambiguous Redirects:** If a user specifies `> *.txt` and 5 text files exist, Bash explicitly traps this as `ambiguous redirect` and aborts. The expansion phase explicitly protects `open()` against passing fragmented `char **` arrays.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Directory targeted for writing (`> /usr`)** | `open_redirection_file()` fails natively via `EISDIR`. | Emits `Is a directory`. Builtin/Command wrapper cancels and returns `1`. |
| **Expansion creates Multiple Files** | Validations fail during wildcard conversion. | Emits `ambiguous redirect`. Cancels. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Nested Descriptor Saving:** Multiple stacked redirections (`> file1 > file2`) execute iteratively. The unwinding `dup2()` mechanics must carefully peel back like an onion from the stack without closing system-critical underlying FDs simultaneously.
