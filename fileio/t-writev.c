#include <sys/uio.h>
#include "tlpi_hdr.h"

ssize_t
t_writev(int fd, const struct iovec *iov, int iovcnt)
{
	ssize_t r = 0, total = 0;
	int i;

	for (i = 0; i < iovcnt; i++) {
		r = write(fd, iov[i].iov_base, iov[i].iov_len);

		if (r == -1)
			errExit("write");

		total += r;
	}

	return total;
}

int main(int argc, char *argv[])
{
	int fd = 1, iovcnt = 2;
	struct iovec iov[iovcnt];
	char str1[3] = { 'a', 'b', '\0' };
	char str2[3] = { 'c', 'd', '\0' };

	iov[0].iov_base = str1;
	iov[0].iov_len = 3;
	iov[1].iov_base = str2;
	iov[1].iov_len = 3;

	if (t_writev(fd, iov, iovcnt) == -1)
		errExit("t_writev");

	exit(EXIT_SUCCESS);
}
