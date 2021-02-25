#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	//int	 n;
	int opened_file;
	int so;
	FILE *file;
	FILE *file2;
	FILE *file3;
	char buf[4096];
	int fildes[2];
	char *path;
	int	res;

	if (argc != 2)
		return (1);

	path = argv[1];
	res = pipe(fildes);
	printf("fildes[0]: %d, fildes[1]: %d\n", fildes[0], fildes[1]);
	if (res < 0)
	{
		perror("failed to pipe");
		return (1);
	}
	so = fileno(stdout);
	res = dup2(fildes[1], so);
	if (res < 0)
	{
		perror("failed to dup2");
		return (1);
	}
	file = fdopen(0, "r");
	//opened_file = open(path, O_RDWR);


	//n = dup(0);
	//fildes[0] = 0;
	//fildes[1] = opened_file;
	//res = pipe(fildes);

	fgets(buf, 4096, file);
	printf("%s", buf);
	//dprintf(2, "%d, %d\n", fildes[1], so);
	//write(1, "a", 1);

	file2 = fdopen(fildes[0], "r");
	close(fildes[0]);
	close(fildes[1]);
	fgets(buf, 4096, file2);
	dprintf(2, "after: %s\n", buf);

	file3 = fopen(path, "w");
	if (file3 == NULL)
	{
		perror("failed to open file");
		return (1);
	}
	//int i = 0;
	//while(buf[i])
	//{
	//	write(2, &buf[i++],  1);
	//}
	res = fputs(buf, file3);
	if (res < 0)
	{
		perror("failed to write");
		return (1);
	}
}
