CC=gcc
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) -std=c11
DEPS=src/calculator.c

calculator: $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o $@


.PHONY: format
format: $(DEPS)
	$(CLANG-FORMAT) -i $(DEPS)

.PHONY: clean
clean:
	$(RM) calculator
