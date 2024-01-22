/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:52 by naadou            #+#    #+#             */
/*   Updated: 2024/01/22 20:35:52 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/errno.h>
# include "Libft/libft.h"

void	free_strs(char **strs);
void	error_exit(char *error, char *var);
int		*ft_open(int ac, char **av, char **envp);
char	*ft_getenv(char *arg, char **envp);
char	*look_for_path(char *cmd, char **envp);

int		strs_len(char **av);
int		wait_for_p(int *pid, char **av);
char	*check_for_vars(char *str, char **envp);

#endif