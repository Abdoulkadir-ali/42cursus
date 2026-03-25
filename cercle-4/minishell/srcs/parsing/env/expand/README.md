# 🔬 List Expansion & Globbing Subpackage (`srcs/parsing/env/expand`)

![Domain](https://img.shields.io/badge/Domain-List_Overwriting_&_Globbing-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Focuses predominantly on iterating an existing token linked-list, orchestrating string-level expansion calls to `split/`, embedding the resulting nodes, and decisively evaluating filesystem wildcard globbing (`*`) using `parsing/wildcard` integrations. 

---

## ⚙️ Core Mechanic & Algorithms
**The Token Replacement Engine (`handle_word_node`):**
1. If the previous token was a heredoc operator (`<<`), **abort expansion**. Heredoc delimiters `<< EOF` must not be manipulated.
2. Delegate the raw token string to `expand_and_split()`.
3. Loop the returned tokens (`process_expanded_list`):
   - Evaluate `is_wildcard()`. If the token is unquoted and contains an active `*`, dispatch `expand_wildcard()`.
   - If matches are found, spawn individual `t_nodes` for every matched file path (`create_token_node_from_match`).
   - If no matches are found, default entirely back to treating the literal `*` string as the command argument.
4. Cleanse `\001` escape markers (`strip_glob_escapes`).
5. Overwrite the original node safely, connecting the previous and next pointers to wrap around the newly inserted expanded node bounds.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Ambiguous Redirect Detection:** Bash forbids redirecting an FD into an unresolvable space. Specifically, `> $UNDEFINED` or `> *.txt` (where `*.txt` resolves to >1 file) must throw `ambiguous redirect`. `process_matches_or_literal()` explicitly checks if the upstream token was a redirection operator. If wildcard lists >1 match or splitting yielded an empty array, it traps the state securely.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Ambiguous Redirect Triggered** | Sets internal `exp.expansion_error = 1`. Keeps literal token layout intact. | `expand_tokens` returns an integer failure code, allowing AST compilation to short-circuit. |
| **No Filesystem Glob Matches** | Discards empty list safely. | Literal token sequence preserved without injection. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Heredoc Delimiter Vulnerability:** Failing to inspect `is_prev_heredoc()` would cause `cat << $USER` to expand the delimiter directly, violating the POSIX heredoc expectation that unquoted bounding strings determine downstream `EOF` evaluation parameters.

---

## 🔌 API Signatures
```c
/**
 * @brief Overwrites tokens with their expanded and globbed sub-variants.
 * @param tokens Double-pointer permitting list-head mutation during insertion.
 * @param env Read-only heap-allocated environment mappings.
 * @param status Active `$?` context numerical.
 * @return 0 on success, non-zero on Ambiguous Redirect failure triggers.
 */
int	expand_tokens(t_nodes **tokens, char **env, int status);
```
