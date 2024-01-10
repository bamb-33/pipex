/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:09:45 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 19:13:35 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	**fourth(void)
{
	char **strs;

	strs = (char **) malloc (3 * sizeof(char *));
	strs[0] = "/bin/ls";
	strs[1] = "/usr/sbin/";
	strs[2] = NULL;
	return (strs);
}
