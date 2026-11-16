#!/usr/bin/env bash
set -u
cd "$(dirname "$0")/.."
pass=0
fail=0
for input in tests/*.in; do
    name="${input%.in}"
    ./sim < "$input" > "${name}.actual"
    if diff -u "${name}.out" "${name}.actual"; then
        echo "PASS ${name}"
        pass=$((pass + 1))
    else
        echo "FAIL ${name}"
        fail=$((fail + 1))
    fi
done
echo "passed=${pass} failed=${fail}"
test "${fail}" -eq 0
