/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:32:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 02:52:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

int		g_last_signal = 0;

/**
 * @brief Initialize signals for a child process to their defaults.
 */
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/**
 * @brief Switch the shell signal behavior to the requested runtime mode.
 * @param mode One of the defined signal modes for interactive, blocking, or
 * heredoc execution.
 * @return This function does not return a value.
 */
void	setup_signals(int mode)
{
	if (mode == SIGNAL_INTERACTIVE)
		setup_signal_mode(handle_interactive);
	else if (mode == SIGNAL_BLOCKING)
		setup_signal_mode(SIG_IGN);
	else if (mode == SIGNAL_HEREDOC)
		setup_signal_mode(handle_heredoc);
	else if (mode == SIGNAL_NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, handle_sigterm);
		rl_event_hook = NULL;
	}
}
