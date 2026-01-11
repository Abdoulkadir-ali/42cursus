#!/bin/bash

export MYVAR=magicword
echo "MYVAR is: '$MYVAR'"

# Generate script
cat > test_case.sh << 'EOF'
cat << $MYVAR
line1
line2
$MYVAR
EOF

echo "--- Script Content ---"
cat test_case.sh
echo "----------------------"

echo "--- Minishell Run ---"
./minishell < test_case.sh > mini.out 2> mini.err
cat mini.out
echo "[Stderr]:"
cat mini.err

echo "--- Bash Run ---"
bash < test_case.sh > bash.out 2> bash.err
cat bash.out
echo "[Stderr]:"
cat bash.err
