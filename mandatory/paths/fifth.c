/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:10:36 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 19:13:45 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	**fifth(void)
{
	char **strs;

	strs = (char **) malloc (3 * sizeof(char *));
	strs[0] = "/bin/ls";
	strs[1] = "/usr/local/bin/";
	strs[2] = NULL;
	return (strs);
}
