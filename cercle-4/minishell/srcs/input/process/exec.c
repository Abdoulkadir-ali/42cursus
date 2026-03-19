/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:48:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:49:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Build an AST for one segment, prepare heredocs, and execute it.
 * @param segment Token list representing one semicolon-delimited segment.
 * @param state Active shell state used during AST execution.
 * @return This function does not return a value.
 */
static void	setup_signals_for_execution(t_shell_state *state)
{
	if (state->interactive_shell)
		setup_signals(SIGNAL_INTERACTIVE);
	else
		setup_signals(SIGNAL_NON_INTERACTIVE);
}

void	execute_ast(t_nodes *segment, t_shell_state *state)
{
	t_ast	*ast;

	ast = ast_builder(segment);
	if (!scan_heredocs(ast, state))
	{
		setup_signals(SIGNAL_BLOCKING);
		state->exit_code = exec_tree(ast, state);
		setup_signals_for_execution(state);
	}
	else
	{
		if (g_last_signal == 130)
			state->exit_code = 130;
		else
			state->exit_code = 1;
	}
	free_ast(ast);
}
