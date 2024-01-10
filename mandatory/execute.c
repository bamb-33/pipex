/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:35:45 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 20:38:52 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	execute_command()
{
	//make this work here and make shorter for the norminate and add the while loop (static var < ac - 3)
	i = 0;
	while (i < 6)
	{
		path = look_for_path(commands[1], i);
		if (path)
			break ;
		i++;
	}
	if (path == 0)
		exit(1);
	fd = open(commands[0], O_RDONLY);
	if (fd == -1)
	{
		printf("fd wasn't opened succefully");
		exit(1);
	}
	infile = read_file(fd);
	cmd = ft_strjoin(path, commands[1]);
	cmd_param = (char **) malloc (sizeof(char *) * 3);
	cmd_param[0] = cmd;
	cmd_param[1] = infile;
	cmd_param[2] = NULL;

	//eventually call a function that will run the final cmd with output of the final - 1 command 
	execve(cmd, cmd_param, NULL);
}