# 🔬 CD Engine Subpackage (`srcs/exec/builtins/functions/cd`)

![Domain](https://img.shields.io/badge/Domain-Directory_Normalization-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
A hyper-specialized engine driving the `cd` builtin. Resolves complex logical directory jumps (`cd -`, `cd ~`, `CDPATH`), executes logical string normalization to safely cancel out `.` and `..` paths locally before interacting with the OS, and guarantees `$PWD` / `$OLDPWD` sync.

---

## ⚙️ Core Mechanic & Algorithms
**The Normalization Pipeline (`normalize_logical`):**
1. Evaluates incoming target string. Extracts a base target route (absolute vs relative to `CWD`).
2. Iterates the string building a visual representation of path fragments, pushing them onto a localized Stack (`collect_components`).
3. While evaluating the Stack:
   - If `.` is seen -> Skip natively.
   - If `..` is seen -> Delete the previous component off the top of the Stack.
4. If the Stack attempts to `-1` beyond the Root `/`, it is capped natively.
5. Emits the rebuilt perfectly normalized logical string back. By executing `chdir()` on THIS string, the shell bypasses OS-level Symlink resolution, keeping user-expectations intact.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **CDPATH Expansion:** If a user specifies a purely relative target (like `cd docs`), Bash natively iterates the `$CDPATH` variable (like `PATH`), prepending each matrix location against `docs` until a valid root is found. `cdpath_find()` honors this behavior exactly, echoing the matched result back to `STDOUT`.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`cd -` invoked without previous jump** | Checks `$OLDPWD`. If NULL, prints `OLDPWD not set`. | Aborts navigation. Returns `1`. |
| **Directory permissions stripped (No Exec)** | `chdir()` call yields `-1`. `handle_cd_error` traps `EACCES`. | Triggers `Permission denied` stderr mapping. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Fallback Physical Traps:** If `normalize_logical()` builds an absolute path that magically yields `-1` when passed to `chdir()`, the `perform_cd()` engine will immediately fall back to passing the raw un-normalized argument to `chdir()`. If this succeeds, `PWD` simply updates to the physical bounds.

---

## 🔌 API Signatures
```c
/**
 * @brief Primary entrance point orchestrating CDPATH, normalization, and OS navigation.
 * @param args Standard argv execution payload (`cd`, `path`).
 * @param state Environment state allowing access to PWD/OLDPWD mutation.
 * @return `0` on traversal, `1` on kernel denial or syntax faults.
 */
int	ft_cd(char **args, t_shell_state *state);
```
