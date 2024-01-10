/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:49:55 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 20:21:00 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*read_file(int fd)
{
	char	*tmp;
	char	*content;

	content = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		content = ft_strjoin(content, tmp);
		tmp = get_next_line(fd);
	}
	return (content);
}