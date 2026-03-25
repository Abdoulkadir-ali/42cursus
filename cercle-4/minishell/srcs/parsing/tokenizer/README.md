# 📦 Tokenizer Subsystem (`srcs/parsing/tokenizer`)

![Subsystem](https://img.shields.io/badge/Subsystem-Lexical_Analysis-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Ultra_Detailed-success?style=for-the-badge)

---

## 🚧 Subsystem Boundary
> [!NOTE]
> **Trigger:** Activated by `input/process` receiving a raw, complete logical text string from the reader.
> 
> **Output:** Converts the raw character array into a sequentially validated, heap-allocated linked list of `t_nodes *tokens`.

---

## ✅ Responsibilities & ❌ Anti-Responsibilities
- **Must:** Skim comments (`#`) and unquoted whitespace securely.
- **Must:** Distinguish structural operators (`|`, `&&`, `>`, etc.) from literal command words.
- **Must:** Run a strict **Syntax Validation Pass** on the extracted nodes before handing them back to the caller.
- **Must Not:** Expand `$VARIABLES` or `*` wildcards (delegated to `parsing/env`).
- **Must Not:** Handle line-continuation logic (delegated strictly to `input/reader`).

---

## 🔄 Internal Sequence Diagram
```mermaid
sequenceDiagram
    participant Process as Caller (input/process)
    participant tok as tokenizer.c
    participant handlers as handlers/
    participant syntax as syntax/

    Process->>tok: tokenizer(char *str)
    
    loop Until End of String
        tok->>tok: skip_spaces_and_comments()
        tok->>handlers: get_next_token()
        
        alt Is Operator Char
            handlers->>handlers: handle_separator()
        else Is Word Char
            handlers->>handlers: handle_word()
        end
        handlers-->>tok: t_token * (Node appended)
    end
    
    tok-->>Process: Raw Token List
    Process->>syntax: check_syntax(tokens)
    
    alt Syntax Valid
        syntax-->>Process: 0 (Success)
    else Syntax Invalid
        syntax-->>Process: 2 (Syntax Error Trapped)
    end
```

---

## 💾 Memory Contracts (Critical)
| Function Allocates | Freeing Responsibility | Condition |
| :--- | :--- | :--- |
| **`get_next_token()`** | `tokenizer()` / Upstream | Allocates individual `t_token` structs and distinct `char *value` slices. If `get_next_token` internally fails (e.g. unclosed quote), it frees itself and returns `NULL`. |
| **`tokenizer()`** | `tokenizer()` / Upstream | Wraps `t_token` data inside `t_nodes` linked lists. If an allocation fails mid-loop, it immediately loops backwards freeing all accumulated nodes via `del_token` before returning `NULL`. |

---

## 🧬 State Mutation Matrix
| Scenario | Mutated Field | Assigned Value |
| :--- | :--- | :--- |
| `check_syntax()` Identifies Sequential Error | `state->exit_code` (Handled by upstream wrapper) | `2` |
| Successful Tokenization | **None** | Pure data transformation; does not touch global state natively. |

---

## 🗂️ Files Inventory
| Subpackage | Primary Function | Role |
| :--- | :--- | :--- |
| `tokenizer.c` | `tokenizer()` | The high-level loop iteratively peeling strings into node blocks. |
| `handlers/` | `get_next_token()` | Subpackage devoted to classifying characters into discrete token chunks. |
| `syntax/` | `check_syntax()` | Subpackage enforcing Bash positional token rules (e.g. tracking `| |`). |