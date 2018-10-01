#include <sys/uio.h>
#include "tlpi_hdr.h"

ssize_t
t_readv(int fd, const struct iovec *iov, int iovcnt)
{
	int i;
	ssize_t r = 0, total = 0;

	for (i = 0; i < iovcnt; i++) {
		r = read(fd, iov[i].iov_base, iov[i].iov_len);

		if (r == -1)
			errExit("read");

		total += r;
	}

	return total;
}

int main(int argc, char *argv[])
{
	int fd = 0, iovcnt = 2, i;
	struct iovec iov[iovcnt];
	char str1[3], str2[3];

	iov[0].iov_base = str1;
	iov[0].iov_len = 3;
	iov[1].iov_base = str2;
	iov[1].iov_len = 3;

	if (t_readv(fd, iov, iovcnt) == -1)
		errExit("t_readv");

	for (i = 0; i < iovcnt; i++)
		printf("%s\n", (char *) iov[i].iov_base);

	if (close(fd) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);
}
