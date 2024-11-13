#include <stdio.h>

int main (int argc, char **argv)
{
	perror("perror line");
	printf("After the perror line\n");

	return 0;
}