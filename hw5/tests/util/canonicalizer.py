#!/usr/bin/env python3

import sys

lines = sys.stdin.readlines()

it = iter(lines)

groups = []
while True:
    try:
        line = next(it).strip()
        tokens = line.split(":")
        if len(tokens) < 1:
            raise ValueError

        key = tokens[0]
        names = []
        while (line := next(it).strip()):
            names.append(line)

        names.sort()

        groups.append({"key": key, "names": names})
    except StopIteration:
        break

groups.sort(key=lambda g: g["key"])
for group in groups:
    print(f"{group['key']}:")
    for name in group["names"]:
        print(name)
    print()
