#!/usr/bin/env python3

import sys

def add_entry_to_table(table, fingerprint, name):
    if fingerprint in table:
        table[fingerprint].append(name)
    else:
        table[fingerprint] = [name]

def index_file(file) -> dict:
    table = {}
    while (line := file.readline()):
        fingerprint, name = line.strip('\n').split('\t')
        add_entry_to_table(table, fingerprint, name)

    return table

def print_entry(digest, group):
    print(f"{digest}:")
    for name in group:
        print(name)

def print_groups(table):
    need_space = False
    for digest, group in table.items():
        if len(group) < 2:
            continue
        if need_space:
            print()

        print_entry(digest, group)
        need_space = True

def main():
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} <file>")
        exit(1)

    filename = sys.argv[1]
    with open(filename, "r") as file:
        table = index_file(file)

    print_groups(table)


if __name__ == '__main__':
    main()

