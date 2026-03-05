/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:06:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_logical_or(t_ast *node, t_shell_state *state)
{
	int	left_status;

	left_status = exec_tree(node->left, state);
	if (left_status != 0)
		return (exec_tree(node->right, state));
	return (left_status);
}

int	exec_logical_and(t_ast *node, t_shell_state *state)
{
	int	left_status;

	left_status = exec_tree(node->left, state);
	if (left_status == 0)
		return (exec_tree(node->right, state));
	return (left_status);
}
