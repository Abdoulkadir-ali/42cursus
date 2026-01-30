/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:08:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

static void	handle_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		write(1, "\n", 1);
	}
}

void	setup_signals(int mode)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (mode == SIGNAL_INTERACTIVE)
	{
		sa.sa_handler = handle_interactive;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == SIGNAL_BLOCKING)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == SIGNAL_HEREDOC)
	{
		sa.sa_handler = handle_heredoc;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}
