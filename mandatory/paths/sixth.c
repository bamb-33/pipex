/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sixth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:11:12 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 19:13:32 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	**sixth(void)
{
	char **strs;

	strs = (char **) malloc (3 * sizeof(char *));
	strs[0] = "/bin/ls";
	strs[1] = "/usr/local/sbin/";
	strs[2] = NULL;
	return (strs);
}
