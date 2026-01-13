CYCLE — What it is and how to use it
====================================
CYCLE — quick guide
===================

Purpose
-------
One iteration of: build → run tester → collect failures → extract repros → fix → repeat.

Quick triage
-----------
1. Run a small cycle: `./tools/run_test_cycle.sh 10`.
2. Open `/tmp/minishell_failures.txt` and pick a case.
3. Find its snippet in `/tmp/minishell_repro.txt` and run under `bash` and `minishell`.
4. Diff stdout/stderr and inspect related source files (`srcs/exec/*`, `srcs/core/main.c`, `srcs/parsing/*`).
5. Make a focused fix and re-run the cycle. After every change, re-run the cycle to verify the fix — that's the point of a cycle.