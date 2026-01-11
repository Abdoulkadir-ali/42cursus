#!/bin/bash

run_test() {
    CMD="$1"
    NAME="$2"
    echo "[$NAME] CMD: $CMD"
    
    echo "$CMD" | ./minishell > mini.out 2> mini.err
    MINI_RET=$?
    echo "$CMD" | bash > bash.out 2> bash.err
    BASH_RET=$?
    
    # Normalize error output (ignore prefix)
    
    # Compare Stdout
    DIFF_OUT=$(diff mini.out bash.out)
    DIFF_ERR=$(diff mini.err bash.err) # Likely different due to prefix "minishell:" vs "bash:"
    
    if [ "$DIFF_OUT" == "" ] && [ "$MINI_RET" == "$BASH_RET" ]; then
        echo "✅ PASS (Stdout & Exit Code match)"
    else
        echo "❌ FAIL"
        echo "   Stdout Diff: [$DIFF_OUT]"
        if [ "$DIFF_OUT" != "" ]; then
             echo "   Mini Out: [$(cat mini.out)]"
             echo "   Bash Out: [$(cat bash.out)]"
        fi
        if [ "$MINI_RET" != "$BASH_RET" ]; then
             echo "   Exit Code Diff: Mini=$MINI_RET, Bash=$BASH_RET"
        fi
        echo "   Mini Err: [$(cat mini.err)]"
        echo "   Bash Err: [$(cat bash.err)]"
    fi
    echo "--------------------------------"
}

export T=e E=c S=h L=o
run_test '$T$E$S$L -n' "Echo Constructed"

export T=E
run_test '$T$E$S$L -n' "Echo Capitalized"

export T=e
run_test '$T$E"c"$L -nn' "ecco Command"
