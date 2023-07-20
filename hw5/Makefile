CC      = clang
CFLAGS  += -gdwarf-4 -O3 -D_GNU_SOURCE -Wall -Wextra -Werror -Wfatal-errors -pedantic -std=c11 -I../lib/include
LDFLAGS += -gdwarf-4 -O3 -L../lib/lib -lcs143

all: groups

groups: groups.o hash.o # add other files here
	$(CC) -o $@ $^ $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm -rf *.o groups
