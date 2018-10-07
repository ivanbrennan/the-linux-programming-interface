CC = gcc

programs = display-env modify-env longjump setjmp-vars mem-segments badjmp setenv unsetenv

lib = ../lib

all: $(programs)

display-env: display_env.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

modify-env: modify_env.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

longjump: longjump.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

setjmp-vars: setjmp_vars.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

mem-segments: mem_segments.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

badjmp: badjmp.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

setenv: setenv.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

unsetenv: unsetenv.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
