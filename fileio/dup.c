#include <fcntl.h>
#include "tlpi_hdr.h"

int
fdup(int oldfd)
{
	int newfd;
	newfd = fcntl(oldfd, F_DUPFD, 0);

	if (newfd == -1)
		exit(EXIT_FAILURE);

	return(newfd);
}

int
main(int argc, char *argv[])
{
	int oldfd, newfd, fd;
	ssize_t nread;
	char buf[1];

	oldfd = 0;
	newfd = fdup(oldfd);

	fd = oldfd;
	while (1) {
		nread = read(fd, &buf, 1);

		if (nread == -1) {
			errExit("read");
		} else if (nread == 0) {
			break;
		} else {
			printf("fd: %d, buf: %c\n", fd, buf[0]);
			fd = (fd == oldfd) ? newfd : oldfd;
		}
	}

	exit(EXIT_SUCCESS);
}
