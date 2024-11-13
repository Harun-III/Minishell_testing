#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

// prototype of pipe
//		int :: pipe(int fildes[2]);
int	main(int argc, char **argv)
{
	int		pipefd[2];
	int		pid;
    char	buffer[BUFFER_SIZE];

	pipe (pipefd);	// this will create two file descriptors:
					// one for reading from the pipe (pipefd[0]) and one for writing to the pipe (pipefd[1]).
	pid = fork();
	if (pid == 0)
	{
		printf("Child: Reading from pipe...\n");
		int bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
		printf("Child: Read %d bytes: %s\n", bytes_read, buffer);
		exit(0);
	}
	else
	{
		const char *message = "Hello from parent!";
		printf("Parent: Writing to pipe...\n");
		write(pipefd[1], message, strlen(message) + 1);
		wait(NULL); // Wait for child to finish
		printf("Parent: Child has finished\n");
	}

	return 0;
	
}