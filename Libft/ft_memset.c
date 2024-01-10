/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:33:49 by naadou            #+#    #+#             */
/*   Updated: 2023/11/14 10:48:39 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	cc;

	i = 0;
	s = (unsigned char *) b;
	cc = (unsigned char) c;
	while (i < len)
	{
		s[i] = cc;
		i++;
	}
	return (b);
}
