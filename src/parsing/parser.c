/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:44 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 22:48:30 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(t_var *var, char *str)
{
	t_command	*head;
	char		*ls;

	if (!str)
		return (NULL);
	ls = ft_strchr(str, '\n');
	if (ls)
		*ls = 0;
	if (*str == 0)
		return (NULL);
	head = parse_list(str);
	var->command_tree = head;
	free(str);
	set_signal_handler(SIGINT, sint_handler_heredoc);
	if (head && parse_here_docs(var, head) == -1)
	{
		var->exit = EXIT_FAILURE;
		if (g_sigint)	
			var->exit = 130;
		free_command_tree(head);
		head = NULL;
	}
	if (!head)
		var->exit = 2;
	set_signal_handler(SIGINT, sint_handler);
	return (head);
}
