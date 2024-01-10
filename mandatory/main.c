/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:37 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 17:49:28 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_get_command(int ac, char **av)
{
	int		i;
	char	*str;
	char	*tmp;
	char	**command;

	i = 1;
	tmp = NULL;
	str = NULL;
	while (i < ac)
	{
		if (str)
			free(str);
		str = strjoin_extra(tmp, av[i], ' ');
		if (tmp)
			free(tmp);
		if (!str)
			exit(1);
		tmp = ft_strdup(str);
		i++;
	}
	command = ft_split(str, ' ');
	// free_strings(str, tmp);
	return (command);
}

int	main(int ac, char *av[])
{
	int		fd;
	char	*tmp;
	char	*infile;
	char	*outfile;
	char	**commands;
	char	*path;
	char	**cmd_param;
	char	*cmd;

	if (ac == 1)
		return (0);
	infile = NULL;
	commands = ft_get_command(ac, av);
	fd = open(commands[0], O_RDONLY);
	tmp = get_next_line(fd);
	while (tmp)
	{
		infile = ft_strjoin(infile, tmp);
		tmp = get_next_line(fd);
	}
	path = look_for_path(commands[1]);

	cmd = ft_strjoin(path, commands[1]);
	cmd_param = (char **) malloc (sizeof(char *) * 3);
	cmd_param[0] = cmd;
	cmd_param[1] = infile;
	cmd_param[2] = NULL;
	execve(cmd, cmd_param, NULL);
	return (0);
}