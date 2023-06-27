LIB   = ./lib
BUILD = ./build
INCLUDE = ./include
SRC     = ./src
UNITTEST = ./unittest
BIN     = ./bin

CC      = clang
CFLAGS  += -g -Wall -Wextra -Werror -Wfatal-errors -pedantic -std=c11 -O3 \
					-I$(INCLUDE)
LDFLAGS += -g -O3 -std=c11 -L./lib

# if you are adding any additional files, please add them here.
UNITS = readline tests array-list linked-list dynamic-buffer

# the list of objects is the list of units + .o suffix
OBJS := $(UNITS:%=$(BUILD)/%.o)

# the list of tests is the list of units + -test suffix
TEST_EXE := $(UNITS:%=$(BIN)/%-test)

lib: $(OBJS)
	ar -crs $(LIB)/libcs143.a $^

test: $(TEST_EXE)

$(BIN)/%-test: $(BUILD)/%-test.o lib
	$(CC) $(LDFLAGS) $< -o $@ -lcs143

$(BUILD)/%-test.o: $(UNITTEST)/%-test.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm -rf $(BUILD)/* $(LIB)/libcs143.a $(BIN)/*-test
