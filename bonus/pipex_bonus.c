/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:59:06 by naadou            #+#    #+#             */
/*   Updated: 2024/01/20 18:27:29 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cmd_excev(char *cmd, char **envp)
{
	char	**argv;
	char	*path;

	argv = ft_split(cmd, ' ');
	if (argv[0][0] == '/')
		path = argv[0];
	else
		path = look_for_path(argv[0], envp);
	if (execve(path, argv, envp) == -1)
	{
		free_strs(argv);
		if (argv[0][0] != '/')
			free(path);
		error_exit(strerror(errno), cmd);
		exit(errno);
	}
}

void	child_p(int fd, int *end, char *cmd, char **envp)
{
	if (fd < 0 || end[1] < 0)
		exit (errno);
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close (end[0]);
	close (end[1]);
	close (fd);
	cmd_excev(cmd, envp);
}

int	last_child_p(int f1, int f2, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(-1);
	if (!pid)
	{
		if (f1 < 0 || f2 < 0)
			exit (errno);
		if (dup2(f2, STDOUT_FILENO) == -1)
			exit(errno);
		if (dup2(f1, STDIN_FILENO) == -1)
			exit (errno);
		close (f1);
		close (f2);
		cmd_excev(cmd, envp);
	}
	close (f1);
	return (pid);
}

int	ft_pipex(char **av, char **envp, int f1, int f2)
{
	static int	i;
	int			end[2];
	pid_t		pid;

	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0 && !i)
		i = 3;
	else if (!i)
		i = 2;
	if (pipe(end) == -1)
		exit(errno);
	pid = fork();
	if (pid < 0)
		exit(errno);
	if (!pid)
		child_p(f1, end, av[i], envp);
	i++;
	close(end[1]);
	close(f1);
	if (av[i + 2] == NULL)
		return (last_child_p(end[0], f2, av[i], envp));
	ft_pipex(av, envp, end[0], f2);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	int	*fds;
	int	pid;
	int	status;

	if (ac < 5 || (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0
			&& ac < 6))
	{
		ft_putendl_fd("invalid number of arguments", 2);
		return (-1);
	}
	fds = ft_open(ac, av, envp);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		close(fds[0]);
		fds[0] = open ("file", O_RDONLY);
	}
	pid = ft_pipex(av, envp, fds[0], fds[1]);
	close(fds[1]);
	free(fds);
	unlink("file");
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	printf("here\n");
	return (0);
}
