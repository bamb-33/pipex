/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:35:45 by naadou            #+#    #+#             */
/*   Updated: 2024/01/11 17:37:59 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**get_execve_params(char *cmd, char *infile, char **flags)
{
	int		i;
	char	**strs;

	i = 1;
	strs = (char **) malloc (sizeof(char *) * (2 + strs_len(flags)));
	strs[0] = cmd;
	while (flags[i])
	{
		strs[i] = flags[i];
		i++;
	}
	strs[i] = infile;
	strs[i + 1] = NULL;
	return (strs);
}

char	**get_execve_params_last(char *cmd, char **flags)
{
	int		i;
	char	**strs;

	i = 1;
	strs = (char **) malloc (sizeof(char *) * (1 + strs_len(flags)));
	strs[0] = cmd;
	while (flags[i])
	{
		strs[i] = flags[i];
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

void	execute_command(char **commands, char *infile)
{
	static int	i;
	int			j;
	char  		*output;
	char  		*path;
	char  		**cmd_flag;
	char  		*cmd;
	char  		**execve_params;
	int			fd_output;
	int			fd[2];
	pid_t		p;
	char buffer[20];

	if (!i)
		i = 1;
	j = 0;
	while (j < 6)
	{
		cmd_flag = ft_split(commands[i], ' ');
		path = look_for_path(cmd_flag[0], j);
		if (path)
			break ;
		j++;
	}
	if (path == 0)
		exit(1);
	cmd = ft_strjoin(path, cmd_flag[0]);
	if (commands[i + 2] == NULL)
	{
		fd_output = open("output", O_RDWR | O_CREAT | O_TRUNC, 0666);
		write(fd_output, infile, ft_strlen(infile));
		execve_params = get_execve_params_last(cmd, cmd_flag);
		for (int z = 0; execve_params[z]; z++)
			printf("%s\n", execve_params[z]);
		if (dup2(fd_output, STDIN_FILENO) == -1) {
        	// Handle the error if necessary
        	perror("dup2");
        	exit(1);
    	}
    	// Close the unnecessary file descriptor
    	close(fd_output);
		execve(cmd, execve_params, NULL);
		exit(0);
	}
	execve_params = get_execve_params(cmd, infile, cmd_flag);
	for (int z = 0; execve_params[z]; z++)
		printf("%s\n", execve_params[z]);
	printf("-------\n");
	i++;
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
		printf("output:\n%s\n", output);
		execute_command(commands, output);
	}
	//eventually call a function that will run the final cmd with output of the final - 1 command 
}
