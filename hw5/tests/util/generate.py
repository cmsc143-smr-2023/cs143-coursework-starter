#!/usr/bin/env python3

import sys
import random

with open('family.txt') as file:
    family = []
    for line in file:
        family.append(line.strip())

with open('names.txt') as file:
    names = []
    for line in file:
        names.append(line.strip())

with open('towns.txt') as file:
    towns = []
    for line in file:
        towns.append(line.strip())

N = 2_500_000

if N <= 20:
    towns = ["A", "B", "C", "D", "E", "F"]

for i in range(N):
    print(f"\r{i}", file=sys.stderr, end='')
    town  = random.choice(towns)
    first = random.choice(names)
    last  = random.choice(family)

    print(f"{town}\t{first} {last}")

print("", file=sys.stderr)
