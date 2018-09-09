CC = gcc

all: copy

copy: copy.c ../lib/error_functions.c
	$(CC) $+ -o $@ -I../lib

clean:
	rm -f copy

.PHONY: all clean
