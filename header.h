/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:52 by naadou            #+#    #+#             */
/*   Updated: 2024/01/16 19:42:41 by naadou           ###   ########.fr       */
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
int		*ft_open(char **av, int ac);
char	**ft_getenv(char **envp);
char	*look_for_path(char *cmd, char **envp);

int	file_existence(char **argv);

#endif