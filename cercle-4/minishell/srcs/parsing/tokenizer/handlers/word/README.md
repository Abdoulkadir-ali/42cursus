# 🔬 Word Handler Subpackage (`srcs/parsing/tokenizer/handlers/word`)

![Domain](https://img.shields.io/badge/Domain-Alphanumeric_Lexing-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Responsible exclusively for peeling sequential alphanumeric, quoted, and parameter characters into distinct `t_token` struct assignments. Distinguishes standard `TOKEN_WORD` targets against valid `TOKEN_PREFIX` environments (like `VAR=1`).

---

## ⚙️ Core Mechanic & Algorithms
**The String Amalgamation Engine (`handle_word`):**
1. Evaluates the leading byte of `str`. If it begins an alphanumeric sequence or quote:
2. Loop continuously, appending substrings (`join_free`) depending on the context mode:
   - **Unquoted Mode:** Read until whitespace or a recognized operator character (`|`, `<`).
   - **Quoted Mode:** Once a `'` or `"` is hit, loop aggressively until the exact matching closing quote is encountered, ignoring embedded spaces entirely.
3. Determine Context Type via `is_assignment_prefix()`:
   - If the assembled string respects `[a-zA-Z_]+=` syntax layout, it promotes the generated token to `TOKEN_PREFIX`.
   - Otherwise, maps default to `TOKEN_WORD`.

---

## 📜 POSIX & Shell Compliance
> [!NOTE]
> **Adjoining Quotes:** `echo "hello"'world'` inherently evaluates to a single contiguous token (`helloworld` internally before expansion layers). The loop inside `handle_word` correctly skips adjoining quote bounds to glue continuous strings into one `char *value` payload.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Unclosed Quotes (`"hello`)** | Evaluator reaches End-of-String (`\0`) without finding the matching bounding quote. Emits `unexpected EOF while looking for matching quote`. | Returns `NULL`. Triggers recursive tokenizer crash. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Prefix Protection:** The `is_assignment_prefix()` mathematical check MUST occur at the *end* of the word assembly, otherwise strings like `VAR="1 2 3"` would break mid-evaluation.

---

## 🔌 API Signatures
```c
/**
 * @brief Isolates unbroken word sequences and handles internal quote toggling.
 * @param str Double-pointer allowing active string mutation.
 * @return Safely isolated `t_token *` matching the Word or Prefix logic.
 */
t_token	*handle_word(char **str);
```
