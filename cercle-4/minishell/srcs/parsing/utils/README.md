# 🔬 Parsing Utilities Subpackage (`srcs/parsing/utils`)

![Domain](https://img.shields.io/badge/Domain-Generic_Data_Structures-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
A collection of generic, stateless helpers used uniformly across the `tokenizer`, `env`, and `ast` bounds. Centralizes node-type comparisons, deterministic memory teardowns for standard shell data structures, and POSIX-compliant syntax error formatting.

---

## ⚙️ Core Mechanic & Algorithms
**The Helper Repertoire:**
1. **Type Comparisons (`token.c`):** 
   - `cmp_node_type()` / `cmp_tok_type()` / `cmp_ast_type()` safely unwrap structures and verify enumerations, mitigating raw NULL-pointer dereferencing errors mid-pipeline.
2. **List Transformations (`token.c`):**
   - `token_list_to_array()` bridges the gap between linked-list parsing logic and native OS contiguous `char **` interfaces (like `execve`), duplicating `TOKEN_WORD` payloads into a sequential heap block.
3. **Memory Annihilation (`utils.c`):**
   - `del_token()` explicitly frees the dynamically allocated `char *value` wrapped inside a token BEFORE freeing the `t_token` struct itself.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Syntax Prompts:** `print_syntax_error()` enforces the strict Bash standard output by printing `minishell: syntax error near unexpected token ` followed by the offending `char *value`, directly to STDERR (`FD 2`).

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Passing `NULL` to comparators** | Safely returns `false` (0). | Allows boolean evaluation loops (like `while(curr)` checks) to gracefully conclude without segfaults. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Struct Ownership:** The wrapper `token_list_to_array()` utilizes `ft_strdup()`. This implicitly means that the caller is now legally responsible for iterating and freeing the returned `char **` matrix manually (via `free_string_array()`), completely independent of the original linked list!

---

## 🔌 API Signatures
```c
/**
 * @brief Annihilates a token and its inner string payload.
 * Useful as a function pointer for `ft_lstclear(&list, del_token)`.
 * @param content Void pointer directly castable to `t_token *`.
 */
void	del_token(void *content);

/**
 * @brief Constructs a contiguous OS-compatible string matrix from tracked tokens.
 * @param tokens Linked list of evaluated parsed nodes.
 * @return NULL-terminated sequence of duplicated strings.
 */
char	**token_list_to_array(t_nodes *tokens);
```
