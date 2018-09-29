#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	int fd, fdA, fdB, nread;
	char buf[1];
	off_t posA, posB;

	fd = open("foofile", O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		errExit("open");
	if (write(fd, "abc\n", 4) != 4)
		errExit("write");
	if (close(fd) == -1)
		errExit("close");

	fdA = open("foofile", O_RDONLY);
	if (fdA == -1)
		errExit("open");
	fdB = dup(fdA);
	if (fdB == -1)
		errExit("dup");

	fd = -1;
	while (1) {
		fd = (fd == fdA) ? fdB : fdA;

		posA = lseek(fdA, 0, SEEK_CUR);
		posB = lseek(fdB, 0, SEEK_CUR);
		if (posA == -1)
			errExit("lseek");
		if (posB == -1)
			errExit("lseek");

		nread = read(fd, buf, 1);
		if (nread == -1) {
			errExit("read");
		} else if (nread == 0) {
			break;
		} else {
			printf("fd%c -> %c (posA: %zd, posB: %zd)\n",
					(fd == fdA) ? 'A' : 'B', buf[0], posA, posB);
		}
	}

	int flagsA, flagsB;
	flagsA = fcntl(fdA, F_GETFL);
	if (flagsA == -1)
		errExit("fcntl");
	flagsB = fcntl(fdB, F_GETFL);
	if (flagsB == -1)
		errExit("fcntl");

	printf("\nflagsA: %d, flagsB: %d\n", flagsA, flagsB);

	if (fcntl(fdA, F_SETFL, O_APPEND) == -1)
		errExit("fcntl");
	flagsA = fcntl(fdA, F_GETFL);
	if (flagsA == -1)
		errExit("fcntl");
	flagsB = fcntl(fdB, F_GETFL);
	if (flagsB == -1)
		errExit("fcntl");

	printf("\nflagsA: %d, flagsB: %d\n", flagsA, flagsB);

	if (close(fdA) == -1)
		errExit("close");
	if (close(fdB) == -1)
		errExit("close");
	if (unlink("foofile") == -1)
		errExit("unlink");

	exit(EXIT_SUCCESS);
}
