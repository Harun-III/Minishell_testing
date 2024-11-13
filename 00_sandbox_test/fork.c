/*
** 
**
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // exit

// WMTE == WHAT_MAIN_TO_EXECUTE
#ifndef WMTE
# define WMTE 0
#endif

#if WMTE==0
int	main()
{
	int	pid;

	pid = fork(); // this line will cause the creation of a new process

	if (pid == 0) // pid of a child always equals 0
	{ // so everything in this 'if' statement will be executed in the child
		printf("pid of child is :%d\n", pid);
		return 0;
	}
	else	
	{ // this will only be executed by the parent process
		printf("pid of parent is :%d\n", pid);
	}

	// What's outside the if-else statement will be executed
	// by both the child and the parent
	printf("My pid is %d\n", getpid());

	return 0;
}
#endif

#if WMTE == 1
int	main()
{
	int pid;

	pid = fork ();

	printf("Technically this line should be printed twice");
}
#endif

// testin wait
// prototype:
//		pitd_t wait(int *stat_loc);
#if WMTE == 2
# include <signal.h> // to use kill
#include <sys/wait.h> // for wait
int	main()
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("I'm the child process i = %d\n", i);
			sleep (1);
		}
	}
	else
	{
		wait(NULL); // this line will make the parent wait for the child to end before continuing
		kill (pid, 2);
		printf("I'm the parent process I just killed my own child\n");
	}
}
#endif

// using int stat_loc with wait
// prototype:
//		pitd_t wait(int *stat_loc); note: stat_loc == status location
#if WMTE == 3
# include <signal.h> // to use kill
# include <sys/wait.h> // for wait
int	main()
{
	int	pid;
	int status_of_child;

	pid = fork();
	if (pid == 0)
	{
		printf("I'm the child process I'll exit with exist status 5\n");
		exit(5);
	}
	else
	{
		wait (&status_of_child); // wait will set the information of the child after it's termination
		printf("I'm the parent process\n");
		printf("\tthe child exit with: %d\n", WEXITSTATUS(status_of_child));
	}
}
#endif