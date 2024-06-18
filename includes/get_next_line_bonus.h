/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 03:34:32 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:28:19 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 4500
# endif

char	*get_next_line(int fd);
char	*manage_left(char **left, char op);
char	ft_strn(char *s, char c, size_t n);
void	ft_cpy(char *dst, char *src, size_t n);

#endif