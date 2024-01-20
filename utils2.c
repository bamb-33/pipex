/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:39:19 by naadou            #+#    #+#             */
/*   Updated: 2024/01/18 19:46:43 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*replace_var(char *env_var, char *var, char *str, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = index + ft_strlen(env_var) + 1;
	new_str = (char *) malloc (sizeof(char)
			* (ft_strlen(var) + (ft_strlen(str) - ft_strlen(env_var) - 1)));
	while (i < index)
	{
		new_str[i] = str[i];
		i++;
	}
	while (*var)
		new_str[i++] = *var++;
	while (str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = 0;
	free (str);
	return (new_str);
}

char	*check_for_vars(char *str, char **envp)
{
	int		i;
	int		j;
	char	*env_var;
	char	*var_value;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i + j] != ' ' && str[i + j] != '\n' && str[i + j])
				j++;
			env_var = ft_substr(str, i + 1, i + j - 1);
			var_value = ft_getenv(env_var, envp);
			if (var_value == NULL)
				return (str);
			str = replace_var(env_var, var_value, str, i);
			free (env_var);
			free (var_value);
			break ;
		}
		i++;
	}
	return (str);
}
