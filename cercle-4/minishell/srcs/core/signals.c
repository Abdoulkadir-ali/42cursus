/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	g_last_signal = 0;

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
		/* Heredoc read loop should check this global or return */
		/* Actually standardized way: close(0) to interrupt read? */
		/* Or just set global and rely on read loop detecting it */
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
		sa.sa_handler = SIG_IGN; /* Ignore in parent, child terminates default */
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
