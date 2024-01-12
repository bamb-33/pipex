/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:59:06 by naadou            #+#    #+#             */
/*   Updated: 2024/01/12 21:51:34 by naadou           ###   ########.fr       */
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
	static int	i;
	int   		end[2];
    pid_t 		pid;

	if (!i)
		i = 2;
	if (pipe(end) == -1)
		exit(-1);
    pid = fork();
    if (pid < 0)
        exit(-1);
    if (!pid)
        child_process(f1, end, av[i], envp);
	wait(0);
	i++;
	if (av[i + 2] == NULL)
		parent_process(f2, end, av[i], envp);
	else
	{
		close(end[1]);
		close(f1);
		ft_pipex(av, envp, end[0], f2);
	}
}

int	main(int ac, char *av[], char **envp)
{
	int		f1;
	int		f2;
	char	*input;

	// if (ac != 5)
	// 	return (-1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		f1 = open ("file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		input = get_next_line(0, av[2]);
		write(f1, input, ft_strlen(input));
		exit(0);
	}
	else
		f1 = open (av[1], O_RDONLY);
	f2 = open (av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(EXIT_FAILURE);
	}
	ft_pipex(av, envp, f1, f2);
	close(f2);
	return (0);
}
