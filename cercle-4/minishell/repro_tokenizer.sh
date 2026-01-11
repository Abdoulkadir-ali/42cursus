#!/bin/bash

# Test cat<<asd
# If tokenizer fails, it sees "cat<<asd" as command -> 127
# If works, it enters heredoc -> prints "success"

echo "Check 1: cat<<asd"
echo -e "cat<<asd\nsuccess\nasd" | ./minishell > out.txt 2> err.txt
RET=$?
cat out.txt
cat err.txt
echo "Exit Code: $RET"

if [ "$RET" == "127" ]; then
    echo "❌ FAIL: Tokenizer failed to split."
else
    echo "✅ PASS: Tokenizer split correctly."
fi
