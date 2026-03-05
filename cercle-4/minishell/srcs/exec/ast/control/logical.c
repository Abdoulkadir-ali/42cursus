/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_logical(t_ast *node, t_shell_state *state, int run_if_zero)
{
	int	left;

	left = exec_tree(node->left, state);
	if ((run_if_zero && left == 0) || (!run_if_zero && left != 0))
		return (exec_tree(node->right, state));
	return (left);
}
