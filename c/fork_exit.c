#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int status;
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		perror("fork() error");
		return (0);
	}
	else if (pid == 0)
	{
		// 子プロセス
		exit(1);
	}
	if (waitpid(pid, &status, 0) != pid)
	{
		perror("failed to waitpid");
		return (1);
	}
	printf("before status: %d\n", status);
	if (WIFEXITED(status))
		printf("status: %d\n", WEXITSTATUS(status));
	return (0);
}
