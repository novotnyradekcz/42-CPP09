#!/usr/bin/env python3

import random
import subprocess
import sys

BINARY = "./PmergeMe"

if len(sys.argv) != 4:
    print("Usage: python3 test_one.py <low> <high> <count>", file=sys.stderr)
    sys.exit(1)

low   = int(sys.argv[1])
high  = int(sys.argv[2])
count = int(sys.argv[3])

nums = [str(random.randint(low, high)) for _ in range(count)]

result = subprocess.run([BINARY] + nums, text=True)
sys.exit(result.returncode)
