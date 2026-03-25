# 🔬 Environment Modifier Subpackage (`srcs/exec/env`)

![Domain](https://img.shields.io/badge/Domain-Kernel_Memory_Mappings-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Centralizes all structural manipulations of `state->envp`. Implements the low-level string arrays shifting required to mutate, inject, rewrite, or drop shell variables. Directly handles the validation rules governing what constitutes a legal Bash identifier name.

---

## ⚙️ Core Mechanic & Algorithms
**The State Rewrite Process (`ft_set_env`):**
1. Evaluates incoming `KEY` + `VALUE` boundaries.
2. Dispatches `get_env_index()` scanning the existing `state->envp` array.
   - **Found (Update):** Natively calls `free()` on the old `KEY=OLD_VAL` pointer. Replaces the index explicitly with a freshly `ft_strdup`'d `KEY=NEW_VAL`.
   - **Not Found (Append):** Allocates a brand new `char **` array sized exactly `N+2` (existing blocks + new block + NULL terminator). Loops and points all old string pointers to the new array matrix. Injects the new `KEY=NEW_VAL` into the penultimate slot. `free()`s the old `char **` matrix shell.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Identifier Character Classes:** Shell natively enforces strict boundaries on what a key can be. The custom validator `is_valid_ident()` guarantees that a key MUST start with `[a-zA-Z_]` and subsequently ONLY contain `[a-zA-Z0-9_]`. Anything else aborts the export attempt and emits a literal non-fatal stderr complaint.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Invalid Identifier Passed (e.g. `export 1VAR=`)** | Rejects action. Dumps `not a valid identifier` to STDERR. | Builtin natively returns Exit Status `1`. Shell continues operation flawlessly. |
| **`malloc()` failure extending the matrix array** | Bypasses modification cleanly. | Triggers fallback without leaking the pre-existing environment heap. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Matrix Freeing Loophole:** When `ft_set_env` expands the environment array into a new, larger matrix allocation, it **strictly frees ONLY the `char **` outer array shell**, NOT the inner strings. The inner strings are simply pointed to by the new matrix. Running a deep free blindly here would nuke the entire environment instance.

---

## 🗂️ Internal Delegation
- **`process/`**: Implements specialized update modifiers targeted directly at dynamic `export` behavior patterns (like explicit list appends `+=`).
