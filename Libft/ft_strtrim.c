/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:31:44 by naadou            #+#    #+#             */
/*   Updated: 2023/11/12 10:40:36 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strdupv2(const char *s1, int counterback, char *scpy)
{
	int		slen;
	int		i;

	slen = ft_strlen(s1) - counterback;
	i = 0;
	while (i < slen)
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = 0;
	return (scpy);
}

static int	ft_cfront(const char *s1, const char *set)
{
	int	i;
	int	counterfront;

	i = 0;
	counterfront = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]))
			counterfront++;
		else
			break ;
		i++;
	}
	return (counterfront);
}

static int	ft_cback(const char *s1, const char *set)
{
	int	i;
	int	counterback;

	i = ft_strlen(s1);
	counterback = 0;
	while (i > 0)
	{
		if (ft_strchr(set, s1[i - 1]))
			counterback++;
		else
			break ;
		i--;
	}
	return (counterback);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		counterfront;
	int		counterback;
	int		strsize;

	if (!s1 || !set)
		return (NULL);
	counterfront = ft_cfront(s1, set);
	counterback = ft_cback(s1, set);
	strsize = ft_strlen(s1) - counterfront - counterback;
	if ((size_t) counterfront == ft_strlen(s1))
	{
		return (ft_strdup(""));
	}
	else
	{
		str = (char *) malloc ((strsize + 1) * sizeof(char));
		if (!str)
			return (NULL);
		str = ft_strdupv2(&s1[counterfront], counterback, str);
	}
	return (str);
}
