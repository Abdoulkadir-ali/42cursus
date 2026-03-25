# 🔬 Export Modifier Helpers (`srcs/exec/env/process`)

![Domain](https://img.shields.io/badge/Domain-Specific_Export_Operators-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Devoted completely to resolving edge-case operators enacted by the `export` builtin. Specifically handles Bash's `+=` syntax that appends values linearly to an existing variable node without dropping the preceding content.

---

## ⚙️ Core Mechanic & Algorithms
**The Advanced Append Engine (`process_export_arg`):**
1. An incoming string like `MY_VAR+=world` is mathematically partitioned.
2. If `+=` is explicitly recognized:
   - Scans `state->envp`.
   - **If Found:** Allocates a new string equivalent to `CURRENT_VAL + "world"`, utilizing `ft_strjoin`. Drops the old inner string and injects the new one.
   - **If Missing:** Behaves identically to a brand new `MY_VAR=world` standard insert, creating the element entirely from scratch.
3. If no special operator is hit, reverts exactly to standard override logic inside `ft_set_env()`.

---

## 📜 POSIX & Shell Compliance
> [!NOTE]
> **Export Null Instantiation:** Bash allows variables to be exported without values (`export NEW_VAR`) placing them in the list natively waiting for future expansions. `create_appended_entry` safely bypasses `=` assignments if they don't explicitly exist in the caller's target.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Invalid Identifier Passed (e.g. `export 1VAR+=val`)** | Fails standard identifier constraint tests. | Prints `not a valid identifier` natively; builtin continues iterating next parameters but sets error state. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Memory Allocation Drift:** The mathematical append `+=` forces a secondary dynamic string `join` immediately preceding the replacement inside the shell tracking matrix. Failure at this secondary allocation phase MUST gracefully rollback the old variable integrity preventing a corrupted shell entry.

---

## 🔌 API Signatures
```c
/**
 * @brief Master dispatcher executing targeted `export` operators including string appends.
 * @param arg Literal user passed export argument ("VAR=val").
 * @param state Active mapping layer holding `envp` arrays.
 */
void	process_export_arg(char *arg, t_shell_state *state);
```
