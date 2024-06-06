/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 03:34:49 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/03 06:37:55 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_append(char *left, char *buff, ssize_t ro)
{
	char	*str;
	size_t	len_left;

	len_left = ft_strlen(left);
	str = (char *) malloc((len_left + ro + 1) * sizeof(char));
	if (!str)
		return (manage_left(&left, 0));
	ft_cpy(str, left, len_left);
	ft_cpy(str + len_left, buff, ro);
	free(left);
	return (str);
}

static char	*ft_cut(char **left, size_t lencut)
{
	size_t	len;
	char	*str;

	if (!(*left)[lencut])
		return (manage_left(left, 0));
	len = ft_strlen(*left);
	str = (char *) malloc((len - lencut + 1) * sizeof(char));
	if (!str)
		return (manage_left(left, 0));
	ft_cpy(str, *left + lencut, len - lencut);
	free(*left);
	return (str);
}

static char	*ft_separe(char **left)
{
	char	*str;
	size_t	len;

	len = 0;
	while ((*left)[len] != 0 && (*left)[len] != '\n')
		len ++;
	if (len == 0 && !(*left)[len])
		return (manage_left(left, 0));
	if ((*left)[len] == '\n')
		len ++;
	str = malloc(len + 1);
	if (!str)
		return (manage_left(left, 0));
	ft_cpy(str, *left, len);
	*left = ft_cut(left, len);
	return (str);
}

static char	*gnl_readline(char *left, char *buff, int fd)
{
	ssize_t	ro;

	ro = BUFFER_SIZE;
	if (!ft_strn(left, '\n', 0))
	{
		while (ro == BUFFER_SIZE && !ft_strn(buff, '\n', ro))
		{
			ro = read(fd, buff, BUFFER_SIZE);
			if (ro < 0)
				return (manage_left(&left, 0));
			left = ft_append(left, buff, ro);
			if (!left)
				return (0);
		}
	}
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left[OPEN_MAX + 1];
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (0);
	left[fd] = manage_left(&(left[fd]), 1);
	if (!left[fd])
		return (0);
	buff = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (manage_left(&(left[fd]), 0));
	left[fd] = gnl_readline(left[fd], buff, fd);
	free(buff);
	if (!left[fd])
		return (0);
	return (ft_separe(&(left[fd])));
}
