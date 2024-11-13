#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	long open_max = sysconf(_SC_OPEN_MAX);

	printf ("max discriptors is: %ld\n", open_max);
}