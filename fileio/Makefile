CC = gcc

programs = copy seek_io
lib = ../lib

all: $(programs)

copy: copy.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

seek_io: seek_io.c $(lib)/error_functions.c $(lib)/get_num.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
