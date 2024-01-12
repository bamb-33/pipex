/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/12 20:25:27 by naadou           ###   ########.fr       */
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

void	child_process(int fd, int *end, char *cmd, char **envp)
{
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close (end[0]);
	close (fd);
	cmd_excev(cmd ,envp);
}

void	parent_process(int fd, int *end, char *cmd, char **envp)
{
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close (end[1]);
	close (fd);
	cmd_excev(cmd ,envp);
}

void	ft_pipex(char **av, char **envp, int f1, int f2)
{
	int   end[2];
    pid_t p;

	if (pipe(end) == -1)
		exit(-1);
    p = fork();
    if (p < 0)
        exit(-1);
    if (!p)
        child_process(f1, end, av[2], envp);
    else
	    parent_process(f2, end, av[3], envp);
}

int	main(int ac, char *av[], char **envp)
{
	int		f1;
	int		f2;

	if (ac != 5)
		return (-1);
	f1 = open (av[1], O_RDONLY);
	f2 = open (av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(EXIT_FAILURE);
	}
	ft_pipex(av, envp, f1, f2);
	close(f1);
	close(f2);
	return (0);
}
