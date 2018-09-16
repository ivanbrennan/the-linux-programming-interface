CC = gcc

programs = copy seek_io tee sparse-copy large_file seek-append atomic_append
lib = ../lib

all: $(programs)

copy: copy.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

seek_io: seek_io.c $(lib)/error_functions.c $(lib)/get_num.c
	$(CC) $+ -o $@ -I$(lib)

tee: tee.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

sparse-copy: sparse-copy.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

large_file: large_file.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib) -D_FILE_OFFSET_BITS=64

seek-append: seek-append.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

atomic_append: atomic_append.c $(lib)/error_functions.c
	$(CC) $+ -o $@ -I$(lib)

clean:
	rm -f $(programs)

.PHONY: all clean
