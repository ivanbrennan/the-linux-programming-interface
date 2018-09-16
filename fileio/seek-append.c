#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	int fd;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH);						/* rw-rw-rw- */
	if (fd == -1)
		errExit("open");

	/* Even though we seek to the beginning of file... */
	if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");

	/* O_APPEND guarantees that any data we write
	 * will be appended to the end of file. */
	if (write(fd, "test\n", 5) != 5)
		errExit("write");

	if (close(fd) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);
}
