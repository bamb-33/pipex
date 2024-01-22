/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/22 20:35:59 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close (end[0]);
	close (end[1]);
	close (fd);
	cmd_excev(cmd, envp);
}

void	last_child_p(int *fds, pid_t *pid, char *cmd, char **envp)
{
	*pid = fork();
	if (*pid < 0)
		exit(-1);
	if (!(*pid))
	{
		if (fds[0] < 0 || fds[1] < 0)
			exit (errno);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(errno);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			exit (errno);
		close (fds[0]);
		close (fds[1]);
		cmd_excev(cmd, envp);
	}
	close (fds[0]);
	close (fds[1]);
}

void	ft_pipex(char **av, char **envp, int *fds, pid_t *pid)
{
	static int	i;
	int			end[2];

	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0 && !i)
		i = 3;
	else if (!i)
		i = 2;
	if (pipe(end) == -1)
		exit(errno);
	*pid = fork();
	if (*pid < 0)
		exit(errno);
	if (!(*pid))
		child_p(fds[0], end, av[i], envp);
	i++;
	pid++;
	close(end[1]);
	close(fds[0]);
	fds[0] = end[0];
	if (av[i + 2] == NULL)
		last_child_p(fds, pid, av[i], envp);
	else
		ft_pipex(av, envp, fds, pid);
}

int	main(int ac, char *av[], char **envp)
{
	int		*fds;
	pid_t	*pid;
	int		status;

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
	pid = (pid_t *) malloc (sizeof(pid_t) * (strs_len(av)));
	ft_pipex(av, envp, fds, pid);
	free(fds);
	unlink("file");
	status = wait_for_p(pid, av);
	return (status);
}
