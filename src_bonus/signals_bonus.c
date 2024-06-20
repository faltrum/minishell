/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	g_sigint;

void	sint_handler_heredoc(int signal)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	g_sigint = signal;
}

void	sint_handler(int signal)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sigint = signal;
}

void	set_signal_mode(int signal, int mode)
{
	struct sigaction	sigs;

	sigemptyset(&sigs.sa_mask);
	sigs.sa_flags = 0;
	if (mode == SIG_IGNORE)
		sigs.sa_handler = SIG_IGN;
	else if (mode == SIG_DEFAULT)
		sigs.sa_handler = SIG_DFL;
	sigaction(signal, &sigs, NULL);
}

void	set_signal_handler(int signal, void (*handler))
{
	struct sigaction	sigs;

	sigs.sa_flags = 0;
	sigs.sa_handler = handler;
	sigemptyset(&sigs.sa_mask);
	sigaction(signal, &sigs, NULL);
}
