/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/12 20:27:20 by naadou           ###   ########.fr       */
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

char	**ft_getenv(char **envp)
{
	char 	**paths;
	char 	*str;
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
