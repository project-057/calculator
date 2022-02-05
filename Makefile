CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
CLANG-SPEC=-fuse-ld=lld --rtlib=compiler-rt -D_CRT_SECURE_NO_WARNINGS
FLAGS=$(CLANG-SPEC) $(WARNING) -std=c11
SRC=src/calculator.c
DEPS=$(SRC) src/eval.h src/eval.c src/utils.h src/variable.h src/stack.h src/stack.c
BINARY=calculator

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
	$(RM) calculator
