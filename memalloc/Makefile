CC = gcc

programs = free_and_sbrk

lib = ../lib

all: $(programs)

free_and_sbrk: free_and_sbrk.c $(lib)/error_functions.c $(lib)/get_num.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
