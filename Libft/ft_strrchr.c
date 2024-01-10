/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:40:46 by naadou            #+#    #+#             */
/*   Updated: 2023/11/12 10:37:57 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		slen;
	char	*str;
	char	cc;

	cc = (char) c;
	str = (char *) s;
	slen = ft_strlen(s);
	while (slen >= 0)
	{
		if (cc == s[slen])
			return (&str[slen]);
		slen--;
	}
	return (0);
}
