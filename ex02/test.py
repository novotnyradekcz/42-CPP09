#!/usr/bin/env python3

import random
import subprocess
import sys

BINARY = "./PmergeMe"

def run(args):
    result = subprocess.run([BINARY] + args, capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr

def check_error(args):
    code, _, _ = run(args)
    return code != 0

def check_sorted(args):
    code, stdout, _ = run(args)
    if code != 0:
        return False
    lines = stdout.strip().split('\n')
    if len(lines) < 2:
        return False
    try:
        after = list(map(int, lines[1].split(': ', 1)[1].split()))
    except (IndexError, ValueError):
        return False
    return after == sorted(int(x) for x in args)

# --- Error input tests ---
error_cases = [
    ([], "no input"),
    (["abc"], "non-number input"),
    (["-1", "3", "5"], "negative number"),
    (["1", "-999"], "negative number mixed"),
]

error_passed = 0
for args, desc in error_cases:
    ok = check_error(args)
    status = "OK" if ok else "FAIL"
    if ok:
        error_passed += 1
    print(f"  [{status}] error case: {desc}")

print()

# --- Valid input tests ---
INT_MAX = 2147483647
lengths = [10, 100, 1000, 10000]
count_per_length = 10
results = {}

for length in lengths:
    passed = 0
    for _ in range(count_per_length):
        nums = [str(random.randint(1, INT_MAX)) for _ in range(length)]
        if check_sorted(nums):
            passed += 1
    results[length] = passed

# --- Summary ---
print("=== Summary ===")
print(f"Error handling:  {error_passed}/{len(error_cases)} correct")
for length in lengths:
    p = results[length]
    print(f"Length {length:>5}:    {p}/{count_per_length} correct")
