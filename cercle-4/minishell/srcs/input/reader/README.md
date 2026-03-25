# 🔬 Input Reader Subpackage (`srcs/input/reader`)

![Domain](https://img.shields.io/badge/Domain-Physical_IO_Interfacing-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Manages physical IO interfacing. Resolves matching delimiters (via `extenders/`), tracks active backslashes, generates context-aware continuation prompts (`>`, `quote>`), and merges multiline inputs safely into single heap-allocated logical string bounds.

---

## ⚙️ Core Mechanic & Algorithms
**The Multiline Accumulator Pipeline:**
1. A physical `char *line` is acquired via `readline()`.
2. Passed into `ext_analyze_input(line)`. If the line possesses unmatched quotes, parens, or trailing `&&`/`||`/`|`/`\`:
   - An op-code is returned.
3. The Reader constructs a `t_line_struct` holding the current buffer and queries `get_multiline_prompt(code)` to fetch the visual string.
4. `read_raw_input()` is called again.
5. The buffers are dynamically joined with `append_with_newline()` OR `append_with_backslash()` based on whether the continuation hook was a physical newline evasion `\`.
6. Goes to Step 2, looping infinitely until `ext_analyze_input()` confirms syntactic closure.

---

## 📜 POSIX & Shell Compliance Hooks
> [!NOTE]
> **Slash Escaping (`append_with_backslash`):** If a user types `\`, the newline itself is swallowed. Bash explicitly strips the `\` from the final array context.

> [!IMPORTANT]
> **Unclosed Quotes EOF Warning:** If an EOF (`Ctrl+D`) arrives while waiting for a closed quote, Bash outputs `unexpected EOF while looking for matching "`. We explicitly implement and fire this exact STDERR string inside `read_and_append_line`.

---

## 🚨 Error & Signal Propagation Table
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`readline()` returns `NULL`** (EOF at base) | `ft_printf_fd("exit\n")` | Loop halts; Program terminates inherently. |
| **`readline()` returns `NULL`** (EOF mid-continuation) | Dumps Bash-compliant error logs to STDERR. | Frees local `line` buffer. Sets `state->syntax_error = 1`. Returns `NULL`. |
| **`g_last_signal == 130` hits** | `readline` returns an empty hook evaluation. | Global loop interprets `g_last_signal` logic upstream. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Double Space Merging:** Ensuring NO double spaces or malformed newlines are injected when `append_with_newline()` binds inputs.

> [!CAUTION]
> **Non-Interactive Piping:** The prompt layer `get_prompt()` must explicitly check `isatty(STDIN_FILENO)` to avoid injecting formatting garbage to standard output chains when pipes feed input data.

---

## 🔌 API Signatures
```c
/**
 * @brief Main entry point fetching a fully closed logical command sentence.
 * @param state Global shell tracking state (pointer).
 * @return Fully allocated `char*` representing the syntactic command line.
 * @throws Returns `NULL` precisely on EOF logic limits.
 */
char	*get_command_line(t_shell_state *state);
```
