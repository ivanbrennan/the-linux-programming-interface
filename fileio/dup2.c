#include <fcntl.h>
#include "tlpi_hdr.h"

int
fdup2(int oldfd, int newfd)
{
	if (oldfd == newfd) {
		if (fcntl(oldfd, F_GETFL) == -1) {
			errno = EBADF;
			return(-1);
		} else {
			return(newfd);
		}
	}

	int fd;
	if (close(newfd) == -1)
		errExit("close");

	fd = fcntl(oldfd, F_DUPFD, newfd);

	if (fd == -1)
		exit(EXIT_FAILURE);

	return(fd);
}

int
main(int argc, char *argv[])
{
	int oldfd, newfd, fd;

	ssize_t nread;
	char buf[1];

	oldfd = 0;
	newfd = fdup2(oldfd, 2);

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
