#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int	write_error(char *s, char *av)
{
	while (*s)
		write(2, s++, 1);
	if (av)
		while (*av)
			write(2, av++, 1);
	write(2, "\n", 1);
	return (1);
}

int	ft_exe(char **av, char **env, int tmp_fd, int i)
{
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(av[0], av, env);
	return (write_error("error: cannot execute ", av[0]));
}

void	execute_commands(char **av, char **env, int tmp_fd)
{
	int	i = 0;
	int	fd[2];

	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (!strcmp(av[0], "cd"))
		{
			if (i != 2)
				write_error("error: cd: bad arguments", NULL);
			else if (chdir(av[1]))
				write_error("error: cd: cannot change directory to ", av[1]);
		}
		else if (i && (!av[i] || !strcmp(av[i], ";")))
		{
			if (!fork())
			{
				if (ft_exe(av, env, tmp_fd, i))
					_exit(1);
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i && !strcmp(av[i], "|"))
		{
			pipe(fd);
			if (!fork())
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (ft_exe(av, env, tmp_fd, i))
					_exit(1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
}

int	main(int ac, char **av, char **env)
{
	int	tmp_fd = dup(STDIN_FILENO);
	(void)ac;
	execute_commands(av, env, tmp_fd);
	return (0);
}
