# 🔬 Operator Handler Subpackage (`srcs/parsing/tokenizer/handlers/operator`)

![Domain](https://img.shields.io/badge/Domain-Punctuation_Lexing-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Responsible exclusively for evaluating an active `str` pointer resting on a known punctuation byte (`|`, `<`, `>`, `&`, `;`, `(`, `)`) and safely extracting multi-byte operator variants (e.g. `<<`, `>>`, `||`, `&&`). 

---

## ⚙️ Core Mechanic & Algorithms
**The Operator Sniffing Algorithm (`handle_separator`):**
1. Evaluates the leading byte.
2. If the leading byte indicates a potential multi-character operator (`<`, `>`, `|`, `&`):
   - Peeks ahead at `*(str + 1)` and `*(str + 2)` to differentiate `>`, `>>`, or `>|`.
   - Bumps the parent `str` pointer forward by the exact length of the match.
   - Triggers `set_token_and_advance()` to cleanly allocate the token node.
3. If it is a generic single-byte terminator (`;`, `(`, `)`):
   - Immediately allocates the token and shifts right by `1`.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Operator Priorities:** Certain tokens like `>|` (clobber overwrite) constitute a distinct single lexeme in Bash instead of two. The peeking algorithms inherently favor the longest valid operator match before falling back.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Invalid Multi-Char Sequence Found** | Like a single `&` byte (which isn't `&&`). Emits standard syntax crash. | Returns `NULL`. Triggers recursive token flushing. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Orphaned Ampersands:** Because Bash background jobs aren't strictly handled the same way as pipelining in our specific shell variant, finding a lone `&` must immediately trigger a Syntax Error rather than lexing successfully. 

---

## 🔌 API Signatures
```c
/**
 * @brief Lexes an operator sequence from the active char pointer.
 * @param str Double-pointer allowing native advancing of the parser head.
 * @return Safely isolated `t_token *` matching the operator logic.
 */
t_token	*handle_separator(char **str);
```
