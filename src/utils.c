/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:23:53 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 02:23:54 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_errloc(size_t size, size_t qty, void **ptr)
{
	*ptr = ft_calloc(qty, size);
	if (!*ptr)
		return (ft_err(-1, STR_MEMORY_ERR, strerror(errno), 0));
	return (0);
}

t_bool	empty_line(char *str)
{
	while (is_blank(*str))
		str ++;
	if (*str == 0)
		return (1);
	return (0);
}

int	get_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
