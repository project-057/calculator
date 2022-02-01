CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) -std=c11
DEPS=src/calculator.c

calculator: $(DEPS)
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
