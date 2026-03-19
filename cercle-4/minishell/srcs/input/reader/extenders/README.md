# input/reader/extenders

Purpose
- Analyze incomplete input lines and decide whether the reader must request
  continuation lines. This submodule encapsulates rules for unmatched quotes,
  parentheses, trailing operators and backslash continuations.

Overview
- Responsibilities split across files:
  - `pairs.c` — scan the line for unmatched quotes and parenthesis depth;
  - `trailing.c` — detect trailing operator tokens that require continuation
    (uses `get_ops()` operator table) and handle escape/backslash rules;
  - `escape.c` — helper to detect whether a trailing backslash is active or
    itself escaped;
  - `extender.c` — public `ext_analyze_input()` entry that combines the checks
    and returns a continuation code (or `0` when the line is complete).

Call flow
1. `ext_analyze_input(line)` is called with the current assembled input.
2. `pairs.c` (`ext_scan_pairs_state`) runs first — it returns a quote char
   when a quote is unclosed, or updates depth for parentheses.
3. If pairs are balanced, `trailing.c` (`check_trailing_op`) scans the last
   non-space character, consults the operator table from `get_ops()` and
   returns an operator code when continuation is required.
4. `escape.c`'s `handle_escape()` is used to ensure a trailing backslash is
   treated as a continuation only when it's not itself escaped.

Continuation codes
- The functions return small char codes indicating the missing construct:
  - quote characters (`'` or `"`) when a corresponding quote is open;
  - `'p'` when parentheses depth is positive (unclosed `(`);
  - `'\'` when a trailing active backslash is detected;
  - operator codes defined by the `get_ops()` table for other trailing ops.

Notes for contributors
- The scanner in `pairs.c` intentionally skips escaped characters when inside
  double-quoted contexts and treats single quotes as literal.
- `trailing.c` includes suppression logic to ignore continuations for repeated
  operator symbols when they are part of a longer repetition immediately
  preceding the detected operator (e.g., `>>>` behavior).

Usage
- Call `ext_analyze_input()` from the reader to decide whether to prompt for
  continuation. The returned code is passed to `get_multiline_prompt()` to
  build the continuation prompt label.
# Input Extender Pipeline

This directory contains the functions that decide whether the current input
line is complete or whether the reader must ask for more lines. The flow below
is function-oriented and follows the exact calls in this subtree.

## Entry Path

`ext_analyze_input` in `extender.c` is the entry point for continuation
analysis.

The steps are:

1. Fetch the operator table through `get_ops()`.
2. Call `check_pairs_state(line)`.
3. If `check_pairs_state` returns a non-zero code, return it immediately.
4. Otherwise call `check_trailing_op(line, ops)`.
5. Return the resulting continuation code, or `0` when the line is complete.

## Quote And Parenthesis Path

`check_pairs_state` decides whether the current line is incomplete because of
unclosed quotes or parentheses.

Its routing is exact:

1. If the line pointer is null, return `0`.
2. Call `check_quote_state(s)`.
3. If a quote remains open, return that quote character.
4. Otherwise call `check_parenthesis_state(s)`.
5. If the returned depth is positive, return `p`.
6. Otherwise return `0`.

`check_quote_state` scans the input and tracks a single active quote context.

Its rules are:

- backslashes are honored outside single quotes
- when no quote is active, `'` or `"` opens a quote context
- when a matching quote is encountered, the quote context closes
- the function returns the unmatched quote character when the scan ends inside
  a quote

`check_parenthesis_state` scans the same line while ignoring characters inside
quotes.

Its rules are:

- backslashes are honored outside single quotes
- opening parentheses increment depth only when no quote is active
- closing parentheses decrement depth only when no quote is active
- the final depth is returned to the caller

Only a positive final depth is treated as a continuation request by
`check_pairs_state`.

## Trailing Operator Path

When quotes and parentheses are balanced, `ext_analyze_input` falls back to
`check_trailing_op` in `trailing.c`.

The steps are:

1. Start from the end of the line.
2. Skip trailing whitespace.
3. If the last non-space character is `\`, call `handle_escape(line, p)`.
4. `handle_escape` counts consecutive backslashes backward from `p`.
5. If the count is odd, return `\\` to request continuation.
6. Otherwise scan the operator definition table.
7. For each operator, compare the end of the line with `ops[i].symbol`.
8. Return `ops[i].code` only for operators whose `counterpart == 0`, excluding
   the backslash code.
9. Return `0` when no continuation-triggering operator is found.

This means the extender asks for another line when the input ends with a lone
escape or an operator that requires a right-hand side.

## Folder-Level Call Chain

The main function chains in this subtree are:

1. `ext_analyze_input` -> `check_pairs_state`
2. `check_pairs_state` -> `check_quote_state` or `check_parenthesis_state`
3. `ext_analyze_input` -> `check_trailing_op` -> `handle_escape`