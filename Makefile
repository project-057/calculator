CC=clang
RM=rm -f
CLANG-FORMAT=clang-format

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) -std=c11
SRC=src/calculator.c 
DEPS=$(SRC) src/eval.h src/utils.h src/variable.h src/vtv.c
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
