/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:24:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Run a built-in command with optional assignment prefixes.
 * @param node AST node whose word is a built-in command.
 * @param state Active shell state used for environment resolution and tracking.
 * @return Exit status returned by the built-in function.
 */
int	exec_builtin_with_assigns(t_ast *node, t_shell_state *state)
{
	char	**saved_env;
	int		status;

	if (save_and_apply_assigns(node, state, &saved_env))
		return (1);
	status = exec_builtin(node->args, state);
	restore_env_and_free(state, saved_env);
	return (status);
}
