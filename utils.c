/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/22 12:44:27 by naadou           ###   ########.fr       */
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
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(var, 2);
}

int	*ft_open(int ac, char **av, char **envp)
{
	int		*fds;
	char	*input;

	fds = (int *) malloc (sizeof(int) * 2);
	if (!fds)
		exit(errno);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		fds[0] = open ("file", O_CREAT | O_RDWR, 0644);
		write(1, "pipe heredoc> ", 14);
		input = check_for_vars(get_next_line(0, av[2]), envp);
		write(fds[0], input, ft_strlen(input) - ft_strlen(av[2]));
		free (input);
		fds[1] = open (av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		fds[0] = open (av[1], O_RDONLY);
		fds[1] = open (av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (fds[0] < 0)
		error_exit(strerror(errno), av[1]);
	if (fds[1] < 0)
		error_exit(strerror(errno), av[ac - 1]);
	return (fds);
}

char	*ft_getenv(char *arg, char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], arg, ft_strlen(envp[i])) == 1)
		{
			str = ft_substr(envp[i], ft_strlen(arg) + 1, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	return (str);
}

char	*look_for_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*str;
	char	*cmd_exec;

	i = 0;
	str = ft_getenv("PATH", envp);
	paths = ft_split(str, ':');
	free(str);
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
