# 🔬 Expansion & Split Subpackage (`srcs/parsing/env/split`)

![Domain](https://img.shields.io/badge/Domain-String_Evaluation_&_Splitting-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
A string-evaluation engine. Responsible for sequentially scanning a single token value, triggering context-aware variable lookup (`$VAR`, `$?`, `$$`), honoring single `''` and double `""` quoting behaviors, stripping literal quotes, and slicing the resulting unquoted strings into disparate tokens via Field Splitting.

---

## ⚙️ Core Mechanic & Algorithms
**The Character-by-Character Evaluation Loop (`run_expansion_loop`):**
1. Evaluate character in context of quoting status (`in_s_quote`, `in_d_quote`).
2. If `$` is found unescaped and outside single quotes -> Look up `get_env_value`. Expand result. 
   - If outside double quotes, trigger **Field Splitting** (`process_val_split()`), converting spaces into definitive token boundaries.
   - If inside double quotes, treat spaces literally and append to current token block.
3. If `\` is found -> Skip formatting if unquoted or specifically escaping nested double-quote bounds. 
4. If `*` is found inside quotes -> Protect it by injecting an internal marker (`\001`) preventing later globbing layers from treating it as an active wildcard.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Empty Quoted Tokens:** A physically empty string typed as `""` must survive tokenization as a definitive empty argument for execution contexts (`echo ""` vs `echo`). `handle_quote_split()` guarantees `has_quotes` flags persist across the boundary to bypass zero-length token culling.

> [!CAUTION]
> **Tilde Pathing:** `~` explicitly expands to `$HOME` ONLY if unquoted and resting isolated or at the prefix pathing bound.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`malloc()` failure appending string chunks** | Dumps partial string buffers. | Returns `NULL`. Triggers recursive cleanup cascaded into `expand_tokens()`. |
| **Variable lookup yields `NULL`** | Replaced implicitly with empty chunk `""`. | If unquoted, token evaporates. If quoted, empty token survives. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **The `\001` Asterisk Escaping Trap:** Because wildcard globbing runs *after* string expansion in our pipeline, passing literal asterisks (like `echo "*"`) relies on `\001` byte-markers. These markers must be strictly stripped by `strip_glob_escapes()` in the `expand/` layer to avoid corrupting `argv` system calls.

---

## 🔌 API Signatures
```c
/**
 * @brief Expands variables and splits unquoted whitespace into a logical node stream.
 * @param str The raw token variable value isolated for processing.
 * @param env Read-only reference to the shell's active environment layer.
 * @param status The current integer value to substitute for `$?`.
 * @return Linked list of `t_nodes` representing the fragmented outputs.
 */
t_nodes	*expand_and_split(char *str, char **env, int status);
```
