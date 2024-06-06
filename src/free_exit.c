/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:13 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/05 06:21:07 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	func_exit(t_var *var)
{
	free_lst(var->env);
	free(var->act);
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
