/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:13 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/09 03:49:12 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_enviroment(t_env *head)
{
	if (!head)
		return ;
	free_enviroment(head->next);
	if (head->name)
		free(head->name);
	if (head->value)
		free(head->value);
	free(head);
}

void	free_word_list(t_word_list *words, int free_word)
{
	if (!words)
		return ;
	free(words->next);
	if (free_word  && words->word)
		free(words->word);
}

void	free_redirects(t_redirect *redirects)
{
	if (!redirects)
		return ;
	free_redirects(redirects->next);
	if (redirects->fd > 2)
		close(redirects->fd);
	free_word_list(redirects->expanded, 1);
	if (redirects->word)
		free(redirects->word);
	free(redirects);
}

void	minishell_cleanup(t_var *var)
{
	if (var->env)
		free_enviroment(var->env);
	if (var->act)
		free(var->act);
	close(var->stdfds[0]);
	close(var->stdfds[1]);
}

void	free_command_tree(t_command *command)
{
	if (!command)
		return ;
	if (command->type == cm_simple && command->value.simple)
	{
		free_word_list(command->value.simple->words, 1);
		free_redirects(command->value.simple->redirects);
		if (command->value.simple->args)
			free_arr(command->value.simple->args);
		free(command->value.simple);
	}
	else if (command->type == cm_connection && command->value.connection)
	{
		free_command_tree(command->value.connection->first);
		free_command_tree(command->value.connection->second);
		free(command->value.connection);
	}
	free(command);
}
