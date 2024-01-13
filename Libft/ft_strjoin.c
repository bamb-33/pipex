/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:17:25 by naadou            #+#    #+#             */
/*   Updated: 2024/01/13 19:23:24 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*ft_put(char *p, char const *s1, char const *s2, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = c;
	while (s2[j])
	{
		p[i + j + 1] = s2[j];
		j++;
	}
	p[i + j + 1] = 0;
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2, char c)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	p = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (p == NULL)
		return (NULL);
	return (ft_put(p, s1, s2, c));
}
