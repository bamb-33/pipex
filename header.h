/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:52 by naadou            #+#    #+#             */
/*   Updated: 2024/01/12 12:38:51 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "Libft/libft.h"

//strjoin_extra
char	*strjoin_extra(char const *s1, char const *s2, char c);

//path_finder
void	free_strs(char **strs);
char	**ft_getenv(char **envp);
char	*look_for_path(char *cmd, char **envp);

//read_file
char	*read_file(int fd);

#endif