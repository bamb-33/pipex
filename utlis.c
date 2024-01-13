/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/13 19:23:18 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	error_exit(char *error, char *var)
{
	ft_putstr_fd(error, 2);
	ft_putendl_fd(var, 2);
	exit(EXIT_FAILURE);
}

int	*ft_open(char **av, int ac)
{
	int		*fds;
	char	*input;

	fds = (int *) malloc (sizeof(int) * 2);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		fds[0] = open ("file", O_CREAT | O_RDWR | O_TRUNC, 0644);
		input = get_next_line(0, av[2]);
		write(fds[0], input, ft_strlen(input) - ft_strlen(av[2]));
		free (input);
	}
	else
		fds[0] = open (av[1], O_RDONLY);
	fds[1] = open (av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds[0] < 0)
		error_exit("zsh: no such file or directory: ", av[1]);
	if (fds[1] < 0)
		error_exit("zsh: no such file or directory: ", av[ac - 1]);
	return (fds);
}

char	**ft_getenv(char **envp)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])) == 1)
		{
			str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			paths = ft_split(str, ':');
			free (str);
			break ;
		}
		i++;
	}
	return (paths);
}

char	*look_for_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmd_exec;

	i = 0;
	paths = ft_getenv(envp);
	while (paths[i])
	{
		cmd_exec = ft_strjoin(paths[i], cmd, '/');
		if (access(cmd_exec, F_OK) == 0)
		{
			free (paths);
			return (cmd_exec);
		}
		free (cmd_exec);
		i++;
	}
	free (paths);
	return (NULL);
}
