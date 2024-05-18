#include "../../includes/Header.h"

void	free_redirects(t_redirect *redirects) 
{
	if (!redirects)
		return;
	free_redirects(redirects->next);
	free(redirects->word);
	if (redirects->fd != 0)
		close(redirects->fd);
	free(redirects);
}

void	free_str_arr(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->type == cm_simple && command->value.simple)
	{
		free_str_arr(command->value.simple->args);
		free_redirects(command->value.simple->redirects);
		free(command->value.simple);
	}
	else if (command->type == cm_connection && command->value.connection) 
	{
		free_command(command->value.connection->first);
		free_command(command->value.connection->second);
		free(command->value.connection);
	}
	free(command);
}

void	free_word_list(t_word_list *words, int free_word) 
{
	t_word_list *aux;

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
