CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) -std=c11 -target x86_64-pc-windows-gnu  -isystem C:\MinGW\include
SRC=src/calculator.c src/eval.c src/utils.c src/stack.c src/string.c
DEPS=$(SRC) src/eval.h src/utils.h src/variable.h src/stack.h src/string.h

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
