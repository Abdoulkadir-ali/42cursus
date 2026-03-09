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