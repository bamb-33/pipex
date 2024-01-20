/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/20 18:14:42 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cmd_excev(char *cmd, char **envp)
{
	char	**argv;
	char	*path;

	argv = ft_split(cmd, ' ');
	if (argv[0][0] == '/')
		path = ft_strdup(argv[0]);
	else
		path = look_for_path(argv[0], envp);
	if (execve(path, argv, envp) == -1)
	{
		free_strs(argv);
		free(path);
		error_exit("command not found", cmd);
		exit(127);
	}
}

void	child_p(int fd, int *end, char *cmd, char **envp)
{
	if (fd < 0 || end[1] < 0)
		exit (errno);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(errno);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		exit(errno);
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
		exit(errno);
	if (!pid)
	{
		if (f1 < 0 || f2 < 0)
			exit (errno);
		if (dup2(f2, STDOUT_FILENO) == -1)
			exit(errno);
		if (dup2(f1, STDIN_FILENO) == -1)
			exit(errno);
		close (f1);
		close (f2);
		cmd_excev(cmd, envp);
	}
	return (pid);
}

int	ft_pipex(char **av, char **envp, int f1, int f2)
{
	int		end[2];
	pid_t	pid;
	pid_t	last_child_pid;

	if (pipe(end) == -1)
		exit(errno);
	pid = fork();
	if (pid < 0)
		exit(errno);
	if (!pid)
		child_p(f1, end, av[2], envp);
	close(end[1]);
	last_child_pid = last_child_p(end[0], f2, av[3], envp);
	close(end[0]);
	return (last_child_pid);
}

int	main(int ac, char *av[], char **envp)
{
	int	*fds;
	int	pid;
	int	status;

	if (ac != 5)
	{
		ft_putendl_fd("invalid number of arguments", 2);
		return (-1);
	}
	fds = ft_open(ac, av, envp);
	pid = ft_pipex(av, envp, fds[0], fds[1]);
	close(fds[0]);
	close(fds[1]);
	free(fds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
