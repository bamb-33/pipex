/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/13 19:58:36 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cmd_excev(char *cmd, char **envp)
{
	char	**argv;
	char	*path;

	argv = ft_split(cmd, ' ');
	path = look_for_path(argv[0], envp);
	if (execve(path, argv, envp) == -1)
	{
		free_strs(argv);
		free(path);
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	child_p(int fd, int *end, char *cmd, char **envp)
{
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close (end[0]);
	close (end[1]);
	close (fd);
	cmd_excev(cmd, envp);
}

void	last_child_p(int f1, int f2, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(-1);
	if (!pid)
	{
		dup2(f2, STDOUT_FILENO);
		dup2(f1, STDIN_FILENO);
		close (f1);
		close (f2);
		cmd_excev(cmd, envp);
	}
}

void	ft_pipex(char **av, char **envp, int f1, int f2)
{
	int		end[2];
	pid_t	p;

	if (pipe(end) == -1)
		exit(-1);
	p = fork();
	if (p < 0)
		exit(-1);
	if (!p)
		child_p(f1, end, av[2], envp);
	close(end[1]);
	last_child_p(end[0], f2, av[3], envp);
	close(end[0]);
}

int	main(int ac, char *av[], char **envp)
{
	int	*fds;

	if (ac != 5)
	{
		ft_putendl_fd("invalid number of arguments", 2);
		return (-1);
	}
	fds = ft_open(av, ac);
	ft_pipex(av, envp, fds[0], fds[1]);
	close(fds[0]);
	close(fds[1]);
	wait(0);
	return (0);
}
