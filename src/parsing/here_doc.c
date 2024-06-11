/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:02 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 03:31:21 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*get_heredoc_line(t_var *var)
{
	char	*line;
	char	*line_skip;

	line = get_next_line(0);
	if (line)
	{
		line_skip = ft_strrchr(line, '\n');
		if (line_skip)
			*line_skip = 0;
	}
	if (g_sigint == SIGINT || !line)
		return (line);
	parameter_expansion(var, &line);
	return (line);
}

int	do_here_doc(t_var *var, t_redirect *redir)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (heredoc_error(fds, NULL));
	while (1)
	{
		write(var->fds_list[1], HEREDOC_PREFIX, 2);
		line = get_heredoc_line(var);
		if (!line && g_sigint != SIGINT)
			ft_err_here_doc(0, WAR_HERE_EOF, redir->word, WAR_HERE_EOF2);
		if (!line || !ft_strcmp(redir->word, line))
			break ;
		if (write(fds[1], line, ft_strlen(line)) \
			== -1 || write(fds[1], \
			END_OF_LINE, ft_strlen(END_OF_LINE)) == -1)
			return (heredoc_error(fds, line));
		free(line);
	}
	if (g_sigint == SIGINT)
		return (heredoc_cleanup(fds, line));
	close(fds[1]);
	redir->fd = fds[0];
	return (0);
}

int	parse_here_docs(t_var *var, t_command *command_tree)
{
	t_redirect *redir;

	if (command_tree->type == cm_simple)
	{
		redir = command_tree->value.simple->redirects;
		while (redir && g_sigint != SIGINT)
		{
			if (redir->type == here_doc && do_here_doc(var, redir) == -1)
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

//			if (g_sigint == SIGINT)
//				return (-1);
