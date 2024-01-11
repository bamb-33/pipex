/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/11 20:54:00 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// char	**ft_argv(char *cmd, char **flags)
// {
// 	int		i;
// 	char	**strs;

// 	i = 1;
// 	strs = (char **) malloc (sizeof(char *) * (1 + strs_len(flags)));
// 	strs[0] = cmd;
// 	while (flags[i])
// 	{
// 		strs[i] = flags[i];
// 		i++;
// 	}
// 	strs[i] = NULL;
// 	return (strs);
// }

void	child_process(int fd, int *end, char *cmd, char **paths)
{
	char	**argv;
	char	**cmd_flags;
	int		j;

	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close (end[0]);
	close (fd);
	argv = ft_split(cmd, ' ');

	path = look_for_path(cmd_flags[0], envp);
	cmd = ft_strjoin(path, cmd_flags[0]);

	execve(cmd, argv, paths);
	exit(EXIT_FAILURE);
}

void	parent_process(int fd, int *end, char *cmd, char **envp)
{
	char	**argv;
	char	**cmd_flags;
	int		j;

	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close (end[1]);
	close (fd);
	argv = ft_split(cmd, ' ');

	path = look_for_path(cmd_flags[0], envp);
	cmd = ft_strjoin(path, cmd_flags[0]);

	execve(cmd, argv, envp);
	exit(EXIT_FAILURE);
}

void	ft_pipex(char **av, char **envp, int f1, int f2)
{
	char **paths;
	int   end[2];
    pid_t p;

	// paths = ft_getenv(envp);
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
		printf("failed to open fds\n");
        return (-1);
	}
	ft_pipex(av, envp, f1, f2);
	return (0);
}