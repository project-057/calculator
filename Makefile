CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
CLANG-SPEC=-fuse-ld=lld --rtlib=compiler-rt -D_CRT_SECURE_NO_WARNINGS
FLAGS=$(CLANG-SPEC) $(WARNING) -std=c11
DEPS=src/calculator.c
BINARY=calculator

$(BINARY): $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o $@

.PHONY: isformatted
isformatted: $(DEPS)
	$(CLANG-FORMAT) -dry-run -Werror $(DEPS)

.PHONY: format
format: $(DEPS)
	$(CLANG-FORMAT) -i $(DEPS)

.PHONY: clean
clean:
	$(RM) calculator
