CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror

FLAGS=$(WARNING) -std=c11 -lm
SRC_WITHOUT_MAIN=src/eval.c src/utils.c src/stack.c src/variable.c src/vtv.c
SRC=src/calculator.c $(SRC_WITHOUT_MAIN)

DEPS=$(SRC) src/eval.h src/utils.h src/variable.h src/stack.h
BINARY=calculator

TEST_SRC=tests/smoke.c
TEST_DEPS=$(TEST_SRC) tests/greatest.h
TEST_BINARY=./test_smoke

$(BINARY): $(DEPS)
	$(CC) $(FLAGS) $(SRC) -o $@

.PHONY: isformatted
isformatted: $(DEPS)
	$(CLANG-FORMAT) -dry-run -Werror $(DEPS)

.PHONY: format
format: $(DEPS)
	$(CLANG-FORMAT) -i $(DEPS)

.PHONY: clean
clean:
	$(RM) $(BINARY)
	$(RM) $(TEST_BINARY)

$(TEST_BINARY): $(TEST_DEPS)
	$(CC) $(FLAGS) $(TEST_SRC) $(SRC_WITHOUT_MAIN) -o $@

.PHONY: test
test: $(TEST_BINARY)
	$(TEST_BINARY)
