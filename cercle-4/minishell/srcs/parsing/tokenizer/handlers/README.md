# 🔬 Token Handlers Subpackage (`srcs/parsing/tokenizer/handlers`)

![Domain](https://img.shields.io/badge/Domain-Character_Extraction-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Serves as the low-level string peeler. Given a raw pointer to a character array, these subpackages evaluate the leading byte, classify it as either a **Terminal Operator** (`|`, `<`, `&`) or a **Word Component** (quotes, alphanumerics), and extract the exact boundary of that segment into an isolated `t_token` struct.

---

## ⚙️ Core Mechanic & Algorithms
**The Handler Delegation Setup:**
1. The orchestrator `get_next_token()` evaluates `*str`.
2. Whitespace is bypassed.
3. If the leading byte matches `|`, `&`, `<`, `>`, `(`, `)`, or `;`:
   - Pass string pointer into `operator/handle_separator()`.
4. If it is any other character (or explicitly quoted):
   - Pass string pointer into `word/handle_word()`.
5. The string pointer `*str` is advanced natively using `ptr++` mathematics within the handlers, consuming the chunk.

---

## 📜 POSIX & Shell Compliance
> [!NOTE]
> **Numeric Redirection Merging:** Operators like `2>` require special handling. If `get_next_token()` extracts a Word consisting purely of integers (e.g. `2`), and the *immediate* next byte belongs to the redirection family (`>`), the handler explicitly merges them into a unified `TOKEN_RED_OUT` holding the value `2>`.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`malloc()` failure building chunk** | Emits standard system failure logs. | Returns `NULL`. Triggers recursive memory rollback upstream in `tokenizer()`. |
| **Unclosed Quotes / Invalid Combinations** | Returns `NULL`. | Caller cascades a Syntax Failure breakdown. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Pointer Traversal:** Handlers actively mutate the source `str` pointer (`char **str`). The upstream loop relies absolutely on the fact that if a handler succeeds, the `str` pointer has been correctly bumped past the last consumed byte. Failing to offset this mathematically results in an infinite Tokenizer loop.

---

## 🗂️ Internal Delegation
- **`operator/`**: Evaluates multicharacter operator clusters (`>>`, `<<<`, `||`).
- **`word/`**: Manages quoting depths and contiguous alphanumeric chunks.
