
#!/bin/bash

run_test() {
    CMD="$1"
    NAME="$2"
    echo "[$NAME] CMD: $CMD"
    
    echo "$CMD" | ./minishell > mini.out 2> mini.err
    MINI_RET=$?
    echo "$CMD" | bash > bash.out 2> bash.err
    BASH_RET=$?
    
    # Normalize error output (remove ./minishell: prefix etc for comparison if needed, but simple existence check is enough for now)
    
    # Compare Stdout
    DIFF=$(diff mini.out bash.out)
    
    if [ "$DIFF" == "" ] && [ "$MINI_RET" == "$BASH_RET" ]; then
        echo "✅ PASS (Stdout & Exit Code match)"
    else
        echo "❌ FAIL"
        if [ "$DIFF" != "" ]; then
            echo "   STDOUT Diff:"
            echo "   Minishell: [$(cat mini.out)]"
            echo "   Bash:      [$(cat bash.out)]"
        fi
        if [ "$MINI_RET" != "$BASH_RET" ]; then
             echo "   EXIT CODE Diff: Mini=$MINI_RET, Bash=$BASH_RET"
        fi
    fi
    echo "--------------------------------"
}

run_test 'echo cd ~' "Tilde Expansion"
run_test 'echo hello world' "Echo Builtin"
run_test 'env ls' "Env with Args" # Should run ls
run_test 'export =test' "Export Invalid ="
run_test 'export 1test' "Export Invalid Num"
