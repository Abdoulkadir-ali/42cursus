/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:17:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_logical_or(t_ast *node, char ***envp)
{
	int	left_status;

	left_status = exec_tree(node->left, envp);
	if (left_status != 0)
		return (exec_tree(node->right, envp));
	return (left_status);
}

int	exec_logical_and(t_ast *node, char ***envp)
{
	int	left_status;

	left_status = exec_tree(node->left, envp);
	if (left_status == 0)
		return (exec_tree(node->right, envp));
	return (left_status);
}
