/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:09 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/19 07:21:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Handle cases where the command expands to nothing
 * but might have assignments.
 * @param new_args Array of expanded command arguments.
 * @param new_assigns Array of expanded assignment strings.
 * @param node Original AST node.
 * @param state Active shell state.
 * @return 0 on success (handled), or -1 if the command is not empty.
 */
static int	handle_empty_new_args(char **new_args, char **new_assigns,
		t_ast *node, t_shell_state *state)
{
	char	**old_assigns;

	if (!new_args || !new_args[0])
	{
		old_assigns = node->assigns;
		node->assigns = new_assigns;
		if (node->assigns)
			apply_assigns_to_state(node, state);
		node->assigns = old_assigns;
		free_string_array(new_args);
		free_string_array(new_assigns);
		return (0);
	}
	return (-1);
}

/**
 * @brief Execute the command with its fully expanded argument
 *  and assignment arrays.
 * @param node Original AST node containing the command structure.
 * @param state Active shell state.
 * @param new_args Fully expanded and split argument list.
 * @param new_assigns Fully expanded and split assignment list.
 * @return Final exit status of the simple command.
 */
static int	run_with_expanded_args(t_ast *node, t_shell_state *state,
		char **new_args, char **new_assigns)
{
	char	**old_args;
	char	**old_assigns;
	int		status;

	old_args = node->args;
	old_assigns = node->assigns;
	node->args = new_args;
	node->assigns = new_assigns;
	if (is_builtin(node->args[0], node->args))
		status = exec_builtin_with_assigns(node, state);
	else
		status = exec_external_with_lookup(node, state);
	node->args = old_args;
	node->assigns = old_assigns;
	free_string_array(new_args);
	free_string_array(new_assigns);
	return (status);
}

/**
 * @brief Execute one simple-command AST node with full dynamic expansion.
 * @param node AST node containing raw command tokens.
 * @param state Active shell state used for expansion and execution.
 * @return Command exit status.
 */
int	exec_simple_command(t_ast *node, t_shell_state *state)
{
	int		status;
	char	**new_args;
	char	**new_assigns;

	new_args = expand_string_array(node->args, state);
	new_assigns = expand_string_array(node->assigns, state);
	status = handle_empty_new_args(new_args, new_assigns, node, state);
	if (status != -1)
		return (status);
	return (run_with_expanded_args(node, state, new_args, new_assigns));
}
