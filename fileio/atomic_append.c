#include <fcntl.h>
#include "tlpi_hdr.h"

/* Test with atomic operation:
 *   fileio/atomic_append f1 1000000 & fileio/atomic_append f1 1000000
 *   wait && ls -l f1
 */

/* Test without atomic operation:
 *   fileio/atomic_append f2 1000000 x & fileio/atomic_append f2 1000000 x
 *   wait && ls -l f2
 * */

int
main(int argc, char *argv[])
{
	int fd, flags, numBytes, i;

	if (argc < 3 || argc > 4)
		usageErr("%s filename num-bytes [x]\n", argv[0]);

	flags = O_WRONLY | O_CREAT;
	if (argc == 3)
		flags |= O_APPEND;

	fd = open(argv[1], flags,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);						/* rw-rw-rw- */
	if (fd == -1)
		errExit("open");

	if (argc == 4)
		if (lseek(fd, 0, SEEK_END) == -1)
			errExit("lseek");

	numBytes = atoi(argv[2]);
	for (i = 0; i < numBytes; i++)
		if (write(fd, "\x0", 1) != 1)
			errExit("write");

	exit(EXIT_SUCCESS);
}
