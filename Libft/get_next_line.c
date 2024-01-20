/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:04:13 by naadou            #+#    #+#             */
/*   Updated: 2024/01/20 20:46:30 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_pipe_here_doc(void)
{
	ft_putstr_fd("pipe heredoc> ", 1);
}

static int	f(char **buffer, char **tmp, char *limiter)
{
	int	j;

	j = 0;
	if (*buffer)
	{
		while ((*buffer)[j])
		{
			if ((*buffer)[j] == '\n' && ft_strncmp(&(*buffer)[j - 3]
			, limiter, ft_strlen(limiter)) == 0)
			{
				if (j - 3 != 0 && (*buffer)[j - 4] != '\n')
				{
					j++;
					continue ;
				}
				free(*tmp);
				return (1);
			}
			j++;
		}
	}
	return (-1);
}

static int	f1(char **buffer, char **tmp, int i)
{
	if (i == -1)
	{
		free(*tmp);
		if (*buffer)
			free(*buffer);
		return (0);
	}
	else if (i == 0 && ft_strlen(*buffer) == 0)
	{
		free(*tmp);
		free(*buffer);
		return (0);
	}
	else if (i == 0)
	{
		free(*tmp);
		*tmp = *buffer;
		*buffer = NULL;
		return (1);
	}
	*buffer = ft_strjoin1(*buffer, *tmp, i);
	if (!(*buffer))
		return (0);
	return (-1);
}

static int	allocation(char **tmp, int fd)
{
	if (BUFFER_SIZE + 1 < 0 || fd == -1 || BUFFER_SIZE + 1 > INT_MAX)
		return (0);
	*tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*tmp))
		return (0);
	if (read(fd, *tmp, 0) == -1)
	{
		free(*tmp);
		return (0);
	}
	(*tmp)[BUFFER_SIZE] = 0;
	return (-1);
}

char	*get_next_line(int fd, char *limiter)
{
	static char	*buffer[256];
	char		*tmp;
	int			i;

	if (allocation(&tmp, fd) == 0)
		return (NULL);
	while (1)
	{
		i = f(&buffer[fd], &tmp, limiter);
		if (i == 1)
			return (buffer[fd]);
		if (buffer[fd] && buffer[fd][ft_strlen(buffer[fd]) - 1] == '\n')
			print_pipe_here_doc();
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == 0 && !buffer[fd])
		{
			free(tmp);
			return (NULL);
		}
		i = f1(&buffer[fd], &tmp, i);
		if (i == 1)
			return (tmp);
		else if (i == 0)
			return (NULL);
	}
}
