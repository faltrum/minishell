/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:02 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	remove_quotes_hdoc(char *str);

static int	heredoc_cleanup(int fds[2], char *line)
{
	close(fds[0]);
	close(fds[1]);
	free(line);
	return (-1);
}

static int	heredoc_error(int fds[2], char *line)
{
	ft_err(0, ERR_HEREDOC, strerror(errno), 0);
	return (heredoc_cleanup(fds, line));
}

static char	*get_heredoc_line(t_var *var, int expand)
{
	char	*line;

	line = readline("> ");
	if (g_sigint == SIGINT || !line)
		return (line);
	if (!expand)
		parameter_expansion(var, &line);
	return (line);
}

static int	do_here_doc(t_var *var, t_redirect *redir, int expand)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (heredoc_error(fds, NULL));
	while (1)
	{
		line = get_heredoc_line(var, expand);
		if (!line && g_sigint != SIGINT)
			ft_err_here_doc(0, WAR_HERE_EOF, redir->word, WAR_HERE_EOF2);
		if (!line || !ft_strcmp(redir->word, line) || g_sigint == SIGINT)
			break ;
		if (write(fds[1], line, ft_strlen(line)) \
			== -1 || write(fds[1], \
			END_OF_LINE, ft_strlen(END_OF_LINE)) == -1)
			return (heredoc_error(fds, line));
		free(line);
	}
	if (g_sigint == SIGINT)
		return (heredoc_cleanup(fds, line));
	free(line);
	close(fds[1]);
	redir->fd = fds[0];
	return (0);
}

int	parse_here_docs(t_var *var, t_command *command_tree)
{
	t_redirect	*redir;

	if (command_tree->type == cm_simple)
	{
		redir = command_tree->value.simple->redirects;
		while (redir && g_sigint != SIGINT)
		{
			if (redir->type == here_doc && \
				do_here_doc(var, redir, remove_quotes_hdoc(redir->word)) == -1)
				return (-1);
			redir = redir->next;
		}
		if (g_sigint != SIGINT)
			return (0);
	}
	else if (command_tree->type == cm_connection && \
		parse_here_docs(var, command_tree->value.connection->first) == 0 && \
		parse_here_docs(var, command_tree->value.connection->second) == 0)
		return (0);
	else
		return (-1);
	return (0);
}
