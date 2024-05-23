#include "../../includes/minishell.h"

t_redirect	*last_redir(t_redirect **redirs)
{
	t_redirect	*move;

	move = *redirs;
	if (move == NULL)
	{
		*redirs = calloc(1, sizeof(**redirs));
		if (!*redirs)
			return (NULL);
		return (*redirs);
	}
	else
	{
		while (move->next)
			move = move->next;
		move->next = calloc(1, sizeof(**redirs));
		if (!move->next)
			return (NULL);
		return (move->next);
	}
}

enum e_redir_type	get_redir_type(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		*i += 2;
		return (append);
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		*i += 2;
		return (here_doc);
	}
	else if (str[*i] == '<')
	{
		(*i)++;
		return (input_redir);
	}
	else
	{
		(*i)++;
		return (output_redir);
	}
}

int	parse_redir(char *str, int *i, t_redirect **redirs)
{
	t_redirect	*redir;

	redir = last_redir(redirs);
	if (!redir)
		return (0);
	redir->type = get_redir_type(str, i);
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '"')
		return (add_quoted_word(str, i, &(redir->word), str[*i]));
	else if (wordchar(str[*i]))
		return (add_normal_word(str, i, &(redir->word)));
	else
	{
		printf("Syntax error, expected file after redirection\n");
		return (0);
	}
}
