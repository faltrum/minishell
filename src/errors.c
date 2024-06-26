/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:08 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/18 21:17:31 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_err(int ret, char *s1, char *s2, char *s3)
{
	char	msg[500];

	msg[0] = 0;
	ft_strlcat(msg, PROGRAM_NAME, 500);
	if (s1)
	{
		ft_strlcat(msg, ERR_SEPARATOR, 500);
		ft_strlcat(msg, s1, 500);
	}
	if (s2)
	{
		ft_strlcat(msg, ERR_SEPARATOR, 500);
		ft_strlcat(msg, s2, 500);
	}
	if (s3)
	{
		ft_strlcat(msg, ERR_SEPARATOR, 500);
		ft_strlcat(msg, s3, 500);
	}
	ft_strlcat(msg, END_OF_LINE, 500);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

int	ft_err_here_doc(int ret, char *s1, char *s2, char *s3)
{
	char	msg[500];

	msg[0] = 0;
	ft_strlcat(msg, PROGRAM_NAME, ft_strlen(PROGRAM_NAME) + 2);
	if (s1)
	{
		ft_strlcat(msg, ": ", 500);
		ft_strlcat(msg, s1, 500);
	}
	if (s2)
		ft_strlcat(msg, s2, 500);
	if (s3)
		ft_strlcat(msg, s3, 500);
	ft_strlcat(msg, END_OF_LINE, 500);
	write(2, msg, ft_strlen(msg));
	return (ret);
}
