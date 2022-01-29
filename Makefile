CC=gcc
RM=rm -f
WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) -std=c11
DEPS=src/calculator.c

calculator: $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o $@

.PHONY: clean
clean:
	$(RM) calculator
