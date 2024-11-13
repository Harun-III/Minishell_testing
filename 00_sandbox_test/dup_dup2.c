/*
** dup and dup2
**		are used for duplicating file descriptors
*/

/*
** dup():
**		duplicate an existing file descriptor.
**		returns the lowest-numbered unused file descriptor.
*/

/*
** dup2():
**		Duplicates an existing file descriptor to 
**		a specified file descriptor.
*/

// WMTE == WHAT_MAIN_TO_EXECUTE
#ifndef WMTE
# define WMTE 0
#endif

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#if WMTE==0
int main()
{
	int	fd;
	int	new_fd;
	int	new_fd_1;


	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);

	new_fd = dup(fd);

	new_fd_1 = dup(fd);

	printf("Original FD: %d, New FD: %d, New FD_2: %d\n", fd, new_fd, new_fd_1);

	write(fd, "Hello ", 6);
	write(new_fd, "World!\n", 7);
	write(new_fd_1, "HELLO\n", 6);

	close(fd);
	close(new_fd);
	close(new_fd_1);

	return 0;
}

#elif WMTE==2
int main()
{
	int fd;

	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);

	dup2(fd, STDOUT_FILENO);

	printf("This will be written to the file instead of the console.\n");

	close(fd);

	return 0;
}

#elif WMTE==1
int main()
{
	int fd;

	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	fd = dup(1);
	write (fd, "hello\n", 6);

	return 0;
}
#endif