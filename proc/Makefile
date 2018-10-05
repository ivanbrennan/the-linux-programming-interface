CC = gcc

programs = display-env

lib = ../lib

all: $(programs)

display-env: display_env.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
