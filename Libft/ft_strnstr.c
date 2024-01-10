/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:58:47 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 15:50:19 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	size_t	needlelen;
	char	*haystack1;

	i = 0;
	needlelen = ft_strlen(needle);
	haystack1 = (char *) haystack;
	while (haystack1[i] && i < len)
	{
		j = 0;
		if (haystack1[i] == needle[j]
			&& ft_strncmp(&haystack1[i], needle, needlelen) == 0
			&& (i + needlelen) <= len)
			return (1);
		i++;
	}
	return (0);
}
