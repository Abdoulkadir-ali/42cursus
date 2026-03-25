# 🧭 Input Module (`srcs/input`)

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Subsystem](https://img.shields.io/badge/Subsystem-Input_Acquisition-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Ultra_Detailed-success?style=for-the-badge)

---

## 🏗️ Architecture TL;DR
> The Input module is the sole gateway for external command text. It is responsible for acquiring physical text lines (interactive or piped), detecting continuation requirements (unmatched delimiters/operators), merging lines, and validating top-level syntax *before* the AST is built or the execution layer is invoked. It operates as a strict pipeline: **Acquisition -> Continuation Merge -> Tokenization -> Syntax Validation -> Segmentation.**

---

## 🗺️ Data Flow Diagram
```mermaid
stateDiagram-v2
    [*] --> reader: get_command_line()
    state reader {
        read_raw_input --> handle_multiline
        handle_multiline --> ext_analyze_input: Check Syntax Needs
        ext_analyze_input --> read_raw_input: Needs Continuation
        handle_multiline --> append_line: Line Merged
    }
    
    reader --> process: return logical line
    state process {
        process_input --> tokenize_and_check
        tokenize_and_check --> check_syntax: Syntax Validation
        check_syntax --> process_segments: Valid Tokens
    }

    process --> ExecuteLayer: Segment Hand-off
    ExecuteLayer --> [*]
```

---

## 🧱 Subsystems Matrix
| Subsystem | Core Responsibility | Consumes | Produces |
| :--- | :--- | :--- | :--- |
| **`reader/`** | Physical line acquisition & continuation merging. | `stdin` or `readline`. | A single complete logical `char *` line. |
| **`process/`** | Tokenization, Syntax Validation, and Semicolon Segmentation. | A complete `char *` line. | Segmented `t_nodes *` token lists ready for AST. |
| **`reader/extenders/`** | Continuation syntax analysis (unmatched quotes/parens). | `char *` buffer segments. | Continuation codes indicating missing counterparts. |

---

## 🧠 Global State Strategy
The `t_shell_state` pointer is passed explicitly to the entry points (`get_command_line` and `process_input`).
- **Mutation Sandbox:** The `input` module *mutates* `state->exit_code` and `state->syntax_error` directly upon detecting tokenization/syntax errors.
- **Handoff:** Before returning to `core`, `process` writes the execution outcome of each segment back to `state->exit_code`.

---

## 🛡️ Error & Signal Philosophy
> [!NOTE]
> **SIGINT (130):** Handled passively. If `g_last_signal == 130` triggers during `readline`, the `reader` safely aborts and frees the buffer.

> [!CAUTION]
> **Syntax Failure:** Always pre-consumes pending heredocs to mimic bash behavior, then clears token allocations safely via `del_token()`.
