/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:40:28 by naadou            #+#    #+#             */
/*   Updated: 2024/01/14 16:12:03 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		slen;
	char	*str;
	char	cc;

	str = (char *) s;
	cc = (char) c;
	i = 0;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (cc == s[i])
			return (&str[i]);
		i++;
	}
	return (0);
}
