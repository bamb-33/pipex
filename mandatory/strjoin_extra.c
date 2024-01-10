/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:34:02 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 13:34:43 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

char	*strjoin_extra(char const *s1, char const *s2, char c)
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