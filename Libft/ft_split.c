/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:18:02 by naadou            #+#    #+#             */
/*   Updated: 2024/01/11 20:09:59 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_strlenv2(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_strdupv2(const char *s1, char c)
{
	char	*scpy;
	int		slen;
	int		i;

	slen = ft_strlenv2(s1, c);
	scpy = (char *) malloc ((slen + 2) * sizeof(char));
	if (!scpy)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != c)
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = '/';
	scpy[i + 1] = 0;
	return (scpy);
}

static int	done(char **str, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == c && c)
		i++;
	while (s[i])
	{
		str[j] = ft_strdupv2(&s[i], c);
		if (!str[j])
			return (1);
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && c)
			i++;
		j++;
	}
	str[j] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	str = (char **) malloc ((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (done(str, s, c) == 1)
		return (malloc_error(str));
	return (str);
}
