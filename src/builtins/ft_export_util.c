/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:41 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 20:14:49 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *identifier)
{
	char	msg[500];

	msg[0] = 0;
	ft_strlcat(msg, EXPORT, 500);
	ft_strlcat(msg, ": `", 500);
	ft_strlcat(msg, identifier, 500);
	ft_strlcat(msg, "': ", 500);
	ft_strlcat(msg, ERR_VALID_IDENTIFIER, 500);
	return (ft_err(-1, msg, 0, 0));
}
