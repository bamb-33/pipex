/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:29 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 17:49:18 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char 	**init(int flag)
{
	char **p1;
	// char *p2;
	// char *p3;
	// char *p4;
	// char *p5;
	// char *p6;
	p1 = (char **) malloc (3 * sizeof(char *));
	p1[0] = "/bin/ls";
	p1[1] = "/bin/";
	p1[2] = NULL;
	// p2 = "/sbin";
	// p3 = "/usr/bin";
	// p4 = "/usr/sbin";
	// p5 = "/usr/local/bin";
	// p6 = "/usr/local/sbin";
	// if (flag == 0)
		return (p1);
	// else if (flag == 1)
	// 	return (p2);
	// else if (flag == 2)
	// 	return (p3);
	// else if (flag == 3)
	// 	return (p4);
	// else if (flag == 4)
	// 	return (p5);
	// else if (flag == 5)
	// 	return (p6);
}

char	*look_for_path(char *cmd)
{
	char	**directories;
	int		fd[2];
	char	*tmp;
	char	*output;
	pid_t	p;

	directories = init(0);
	if (pipe(fd) == -1)
	{
		printf("\nError: Could not create a pipe!\n");
        exit(-1);
    }
    p = fork();
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
		tmp = get_next_line(fd[0]);
		while (tmp)
		{
			output = ft_strjoin(output, tmp);
			tmp = get_next_line(fd[0]);
		}
		if (ft_strnstr(output, cmd, ft_strlen(output)) == 1)
			return (directories[1]);
	}
	return (0);
}
