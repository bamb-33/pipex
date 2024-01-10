/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:35:45 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 22:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**get_execve_params(char *cmd, char *infile)
{
	char	**strs;

	strs = (char **) malloc (sizeof(char *) * 3);
	strs[0] = cmd;
	strs[1] = infile;
	strs[2] = NULL;
	return (strs);
}

void	execute_command(char **commands, char *infile)
{
	static int	i;
	int			j;
	char  		*output;
	char  		*path;
	char  		*cmd;
	char  		**execve_params;
	int			fd[2];
	pid_t		p;

	if (!i)
		i = 1;
	j = 0;
	while (j < 6)
	{
		path = look_for_path(commands[i], i);
		if (path)
			break ;
		j++;
	}
	if (path == 0)
		exit(1);
	cmd = ft_strjoin(path, commands[i]);
	execve_params = get_execve_params(cmd, infile);
	while (commands[i + 1])
	{
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
			dup2(fd[1], STDOUT_FILENO);
			execve(cmd, execve_params, NULL);
		}
		else
		{
			close(fd[1]);
			wait(NULL);
			output = read_file(fd[0]);
			execute_command(commands, output);
		}
	}
	//eventually call a function that will run the final cmd with output of the final - 1 command 
}
