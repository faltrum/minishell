/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/17 09:30:10 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint;

void	sint_handler_heredoc(int signal)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
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

void	squit_handler(int signal)
{
	kill(signal, 0);
}

void	set_signal_ignore(int signal)
{
	struct sigaction	sigs;

	sigs.sa_flags = 0;
	sigs.sa_handler = SIG_IGN;
	sigemptyset(&sigs.sa_mask);
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
