/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naadou <naadou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:52 by naadou            #+#    #+#             */
/*   Updated: 2024/01/10 19:25:25 by naadou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "Libft/libft.h"

//strjoin_extra
char	*strjoin_extra(char const *s1, char const *s2, char c);

//path_finder
char	*look_for_path(char *cmd, int flag);

//read_file
char	*read_file(int fd);

//paths/*.c
char	**first(void);
char	**second(void);
char	**third(void);
char	**fourth(void);
char	**fifth(void);
char	**sixth(void);

#endif