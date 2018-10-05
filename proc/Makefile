CC = gcc

programs = display-env modify-env longjump

lib = ../lib

all: $(programs)

display-env: display_env.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

modify-env: modify_env.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

longjump: longjump.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
