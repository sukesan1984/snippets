#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
        char **argv;
        pid_t pid;
		int res;
		int fd;

        //argv = calloc(3, sizeof(char *));
        //argv[0] = "/bin/cat";
        //argv[1] = "test";
        //argv[2] = NULL;
        argv = calloc(2, sizeof(char *));
        argv[0] = "/bin/cat";
        argv[1] = NULL;

		fd = open("test", O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			perror("open error");
			exit(1);
		}

		res = dup2(fd, 0);
		if (res < 0)
		{
			perror("dup2 error");
			exit(1);
		}

        if ((pid = fork()) < 0)
        {
                perror("fork error");
                exit(1);
        }
        else if (pid == 0)
        {
                // 子プロセス
                execv("/bin/cat", argv);
                exit(1);
        }

        return (0);
}

