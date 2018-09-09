#include <fcntl.h>
#include <stdbool.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
	int opt, outputFd, openFlags;
	bool append = false;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	while ((opt = getopt(argc, argv, ":a")) != -1) {
		switch (opt) {
			case 'a': append = true; break;
			case '?': usageErr("%s: unrecognized option (%c)", argv[0], optopt);
			default: fatal("Unexpected case in switch()");
		}
	}

	if (optind != argc -1)
		usageErr("%s [-a] file\n", argv[0]);

	if (append)
		openFlags = O_CREAT | O_WRONLY | O_APPEND;
	else
		openFlags = O_CREAT | O_WRONLY | O_TRUNC;

	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;	/* rw-r--r-- */
	outputFd = open(argv[optind], openFlags, filePerms);
	if (outputFd == -1)
		errExit("opening file %s", argv[optind]);

	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
		if (write(outputFd, buf, numRead) != numRead)
			fatal("couldn't write whole buffer");
		if (write(STDOUT_FILENO, buf, numRead) != numRead)
			fatal("couldn't write whole buffer");
	}
	if (numRead == -1)
		errExit("read");

	if (close(outputFd) == -1)
		errExit("close file");

	exit(EXIT_SUCCESS);
}
