/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:13 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:07 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	free_word_list(words->next, free_word);
	if (free_word && words->word)
		free(words->word);
	free (words);
}

void	free_redirects(t_redirect *redirects)
{
	if (!redirects)
		return ;
	free_redirects(redirects->next);
	if (redirects->fd > 2)
		close(redirects->fd);
	if (redirects->word && \
		(!redirects->expanded || redirects->expanded->word != redirects->word))
		free(redirects->word);
	free_word_list(redirects->expanded, 1);
	free(redirects);
}

void	minishell_cleanup(t_var *var)
{
	if (var->env)
		free_enviroment(var->env);
	if (var->act)
		free(var->act);
	close(var->fds_list[0]);
	close(var->fds_list[1]);
	if (var->fds_list[2] != -1)
		close (var->fds_list[2]);
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
			free(command->value.simple->args);
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
