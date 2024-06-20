/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:44 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_command	*parser(t_var *var, char *str)
{
	t_command	*head;

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
	else if (!head)
		var->exit = 2;
	set_signal_handler(SIGINT, sint_handler);
	return (head);
}
