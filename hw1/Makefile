CC      = clang
CFLAGS  += -g -Wall -Wextra -Werror -pedantic -std=c11
LDFLAGS += -g

all: cat diffw

test: readline-test substring-test

cat: cat.o readline.o dynamic-buffer.o
	$(CC) $(LDFLAGS) -o $@ $^

diffw: diffw.o readline.o substring.o dynamic-buffer.o
	$(CC) $(LDFLAGS) -o $@ $^

readline-test: readline-test.o readline.o dynamic-buffer.o
	$(CC) $(LDFLAGS) -lcriterion -o $@ $^

substring-test: substring-test.o substring.o dynamic-buffer.o
	$(CC) $(LDFLAGS) -lcriterion -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm -rf *.o cat diffw readline-test substring-test
