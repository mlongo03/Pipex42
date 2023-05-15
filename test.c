
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int fdfile1;
	int fdfile2;
	int fd[2];

	fdfile1 = open(argv[1], O_RDONLY);
	fdfile2 = open(argv[4], O_WRONLY | O_TRUNC);
	if (pipe(fd) == -1)
		return (0);

	int pid1 = fork();
	if (pid1 < 0)
		return (0);

	if (pid1 == 0)
	{
		dup2(fdfile1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fdfile1);
		close(fdfile2);
		execlp("cat", "cat", NULL);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return (0);

	if (pid2 == 0)
	{

		dup2(fdfile2, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fdfile2);
		close(fdfile1);
		execlp("grep", "grep", "come", NULL);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
