/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 19:27:44 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char 	**init(int flag)
{
	if (flag == 0)
		return (first());
	else if (flag == 1)
		return (second());
	else if (flag == 2)
		return (third());
	else if (flag == 3)
		return (fourth());
	else if (flag == 4)
		return (fifth());
	else if (flag == 5)
		return (sixth());
	return (0);
}

char	*look_for_path(char *cmd, int flag)
{
	char	**directories;
	char	*output;
	int		fd[2];
	pid_t	p;

	directories = init(flag);
	if (pipe(fd) == -1)
	{
		printf("\nError: Could not create a pipe!\n");
        exit(-1);
    }
    p = fork();
	if (p == -1)
	{
		printf("\nError: Could not fork!\n");
        exit(-1);
	}
	if (p == 0)
	{
		close(fd[0]);
		int original_stdout = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve ("/bin/ls", directories, NULL);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		output = read_file(fd[0]);
		if (ft_strnstr(output, cmd, ft_strlen(output)) == 1)
			return (directories[1]);
	}
	return (NULL);
}
