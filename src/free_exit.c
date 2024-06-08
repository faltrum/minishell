/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:13 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/09 01:14:01 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_enviroment(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

void	minishell_cleanup(t_var *var)
{
	free_enviroment(var->env);
	free(var->act);
	close(var->stdfds[0]);
	close(var->stdfds[1]);
	free(var);
}

void	free_redirects(t_redirect *redirects)
{
	if (!redirects)
		return ;
	free_redirects(redirects->next);
	free(redirects->word);
	if (redirects->fd != 0)
		close(redirects->fd);
	free(redirects);
}

void	free_command_tree(t_command *command)
{
	if (!command)
		return ;
	if (command->type == cm_simple && command->value.simple)
	{
		free_arr(command->value.simple->args);
		free_redirects(command->value.simple->redirects);
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

void	free_word_list(t_word_list *words, int free_word)
{
	t_word_list	*aux;

	while (words)
	{
		aux = words->next;
		if (free_word)
		{
			free(words->word);
			words->word = NULL;
		}
		free(words);
		words = aux;
	}
}
