#include <unistd.h>
#include <stdio.h>

/*

int	execve(const char *path, char *const argv[], char *const envp[]);
pid_t fork(void);
*/
// #include <wait.h>
#include <unistd.h>
#include <sys/wait.h>

int		main(int argc, char **argv, char **env)
{

	int main_id = getpid();
	int exit_status;

	int forked = fork();
	// if (forked)
	// 	printf("this is main process with id %d\n", main_id);
	if (!forked)
	{
		printf("this is child process pid: %d\n", forked);
		printf("this is child process main id is %d\n", main_id);
		// sleep (3);
		execve("/bin/ls", argv, env);

	}
		sleep (1);
		printf("before fork end\n");
		waitpid(forked, &exit_status, 0);
		// 00000000 00000000 00000000 00000000
		printf("exit status is: %d\n", WEXITSTATUS(exit_status));

		// sleep (3);
		printf("helllooo\n");


		// waitpid(forked, &exit_status, 0);
}
