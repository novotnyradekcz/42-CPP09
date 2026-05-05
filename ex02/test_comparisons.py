#!/usr/bin/env python3

import random
import subprocess
import math

BINARY = "./PmergeMe"

def run(args):
    result = subprocess.run([BINARY] + args, capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr

def theoretical_min(n):
    """Lower bound on worst-case comparisons to sort n elements: ceil(log2(n!))"""
    if n <= 1:
        return 0
    return math.ceil(sum(math.log2(i) for i in range(1, n + 1)))

def parse_comparisons(stdout):
    """Extract comparison counts from output lines 5 and 6 (1-indexed)."""
    lines = stdout.strip().split('\n')
    if len(lines) < 6:
        return None, None
    vec_line = lines[4]
    deq_line = lines[5]
    if not vec_line.startswith("Comparisons (vector):") or \
       not deq_line.startswith("Comparisons (deque):"):
        return None, None
    try:
        vec_count = int(vec_line.split(':')[1].strip())
        deq_count = int(deq_line.split(':')[1].strip())
        return vec_count, deq_count
    except (IndexError, ValueError):
        return None, None

# Probe to check if comparison output is enabled
_, stdout, _ = run(["1", "2", "3", "4", "5"])
vec, deq = parse_comparisons(stdout)

if vec is None:
    print("Comparisons not found in program output.")
    print("To enable, uncomment this line in PmergeMe.hpp:")
    print("  // #define COUNT_COMPARISONS")
    print("Then rebuild with 'make re' and run this tester again.")
    exit(0)

print("Comparison counter active. Running 10 random sequences per length for n where Ford-Johnson is optimal (Knuth, TAOCP).\n")

# Ford-Johnson achieves the theoretical minimum only for these lengths
OPTIMAL_LENGTHS = list(range(1, 12)) + [20, 21]

INT_MAX = 2147483647
RUNS = 10

print(f"{'n':>3}  {'theory':>6}  {'vec max':>8}  {'deq max':>8}  {'vec ok':>6}  {'deq ok':>6}")
print("-" * 52)

for n in OPTIMAL_LENGTHS:
    theory = theoretical_min(n)
    vec_max = 0
    deq_max = 0
    for _ in range(RUNS):
        nums = [str(random.randint(1, INT_MAX)) for _ in range(n)]
        _, out, _ = run(nums)
        v, d = parse_comparisons(out)
        if v is not None:
            vec_max = max(vec_max, v)
        if d is not None:
            deq_max = max(deq_max, d)
    vec_ok = "OK" if vec_max <= theory else "FAIL"
    deq_ok = "OK" if deq_max <= theory else "FAIL"
    print(f"{n:>3}  {theory:>6}  {vec_max:>8}  {deq_max:>8}  {vec_ok:>6}  {deq_ok:>6}")
