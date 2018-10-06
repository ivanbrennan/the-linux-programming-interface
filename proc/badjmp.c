#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env;

static void
f1(void)
{
	int i = setjmp(env);

	if (i < 3) {
		printf("%d\n", i);
		longjmp(env, i + 1);
	}
}

int
main(int argc, char *argv[])
{
	f1();

	longjmp(env, 1);	/* Leads to incoherent jump behavior and an eventual
						   segmentation fault because we're jumping into a
						   function that has already returned. */

	exit(EXIT_SUCCESS);
}
