/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:04:24 by naadou            #+#    #+#             */
/*   Updated: 2023/11/12 10:27:23 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*scpy;
	int		slen;
	int		i;

	i = 0;
	slen = ft_strlen(s1) + 1;
	scpy = (char *) malloc (slen * sizeof(char));
	if (!scpy)
		return (0);
	while (i < slen)
	{
		scpy[i] = s1[i];
		i++;
	}
	return (scpy);
}
