/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:12 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/18 17:16:44 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*allocate_last_redir(t_redirect **redirs)
{
	t_redirect	*move;

	move = *redirs;
	if (*redirs == NULL)
	{
		ft_errloc(sizeof(t_redirect), 1, (void **)redirs);
		return (*redirs);
	}
	else
	{
		while (move->next)
			move = move->next;
		ft_errloc(sizeof(t_redirect), 1, (void **)&(move->next));
		return (move->next);
	}
}

static enum e_redir_type	get_redir_type(char *str, int *i)
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

static void	remove_quotes_hdoc(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i;
			while (str[j])
			{
				str[j] = str[j + 1];
				j ++;
			}
		}
		else
			i ++;
	}
}

int	parse_redir(char *str, int *i, t_redirect **redirs)
{
	t_redirect	*redir;
	int			exit;

	redir = allocate_last_redir(redirs);
	if (!redir)
		return (-1);
	redir->type = get_redir_type(str, i);
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '"' || is_regular(str[*i]))
	{
		exit = add_word(str, i, &(redir->word));
		if (exit == 0 && redir->type == here_doc)
			remove_quotes_hdoc(redir->word);
		return (exit);
	}
	else
		return (ft_err(-1, ERR_SYNTAX_REDIRECTION, 0, 0));
}
