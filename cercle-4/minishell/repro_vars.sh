#!/bin/bash
X="  A  B  "
echo "Test 1:"
/bin/echo "1"$X'2'

X=" A  B  "
echo "Test 2:"
/bin/echo "1"$X'2'

X="A  B  "
echo "Test 3:"
/bin/echo "1"$X'2'

X="  A  B "
echo "Test 4:"
/bin/echo "1"$X'2'

X="  A  B"
echo "Test 5:"
/bin/echo "1"$X'2'

X=""
echo "Test empty:"
/bin/echo "1"$X'2'

X=" "
echo "Test space:"
/bin/echo "1"$X'2'
