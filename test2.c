#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			break;
		i++;
	}
	printf("%s", envp[i]);
}
