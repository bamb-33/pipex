/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/11 20:43:09 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_getenv(char **envp)
{
	char 	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])) == 1)
		{
			paths = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':');
			break ;
		}
		i++;
	}
	return (paths);
}

// char 	**init(int flag)
// {
// 	if (flag == 0)
// 		return (first());
// 	else if (flag == 1)
// 		return (second());
// 	else if (flag == 2)
// 		return (third());
// 	else if (flag == 3)
// 		return (fourth());
// 	else if (flag == 4)
// 		return (fifth());
// 	else if (flag == 5)
// 		return (sixth());
// 	return (0);
// }

char	*look_for_path(char *cmd, char paths)
{
	char	**arg;
	char	*output;
	int   end[2];
    pid_t p;

	if (pipe(end) == -1)
		exit(-1);
    p = fork();
    if (p < 0)
         exit(-1);
	if (p == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		execve ("/bin/ls", arg, NULL);
	}
	else
	{
		close(end[1]);
		wait(NULL);
		output = read_file(end[0]);
		if (ft_strnstr(output, cmd, ft_strlen(output)) == 1)
			return (directories[1]);
	}
	return (NULL);
}
