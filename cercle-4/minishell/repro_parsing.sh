#!/bin/bash

# Test quote expansion

echo "Check 1: Single inside Double"
echo "echo \"'\$USER'\"" | ./minishell > mini.out
# Expect: 'value' (e.g. 'abdali')

echo "Check 2: Double inside Single"
echo "echo '\"\$USER\"'" | ./minishell >> mini.out
# Expect: "$USER" (literal)

cat mini.out
