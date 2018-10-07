#include "tlpi_hdr.h"

extern char **environ;

int
unsetenvf(const char *name)
{
	char **ep, **p;
	int i;
	size_t len = strlen(name);

	for (ep = environ; *ep != NULL; ep++) {
		while (*ep != NULL) {
			i = 0;
			while (i < len && (*ep)[i] == name[i])
				i++;

			if (i == len && (*ep)[len] == '=') {	/* Found name=            */
				for (p = ep; *p != NULL; p++) {		/* Remaining elements,    */
					*p = *(p+1);					/* shift by one position. */
				}
			} else {
				break;
			}
		}
	}

	return 0;
}

int
main(int argc, char *argv[])
{
	char *name = argv[1];
	char *value;

	value = getenv(name);
	if (value == NULL)
		printf("%s is unset\n", name);
	else
		printf("%s=%s\n", name, value);

	if (unsetenvf(name) != 0)
		errExit("unsetenv");

	value = getenv(name);
	if (value == NULL)
		printf("%s is unset\n", name);
	else
		printf("%s=%s\n", name, value);

	exit(EXIT_SUCCESS);
}
