#include "tlpi_hdr.h"

int
setenvf(const char *name, const char *value, int overwrite)
{
	static char *str;

	if (getenv(name) != NULL && overwrite == 0)
		return 0;

	str = malloc(strlen(name) + strlen(value) + 1);
	if (str == NULL)
		errExit("malloc");

	if (sprintf(str, "%s=%s", name, value) < 0)
		errExit("sprintf");

	return putenv(str);
}

int
main(int argc, char *argv[])
{
	char *name = argv[1];
	char *newval = argv[2];
	int overwrite = atoi(argv[3]);
	char *value;

	value = getenv(name);
	if (value == NULL)
		printf("%s is unset\n", name);
	else
		printf("%s = %s\n", name, value);

	if (setenvf(name, newval, overwrite) != 0)
		errExit("setenvf");

	value = getenv(name);
	if (value == NULL)
		printf("%s is unset\n", name);
	else
		printf("%s = %s\n", name, value);

	exit(EXIT_SUCCESS);
}
