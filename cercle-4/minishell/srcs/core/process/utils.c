/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:55:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	expand_and_check_error(t_nodes **segment, char **envp, int exit_code,
		int *new_exit_code)
{
	expand_tokens(segment, envp, exit_code);
	if (g_expansion_error)
	{
		*new_exit_code = g_exit_code;
		ft_lstclear(segment, del_token);
		g_expansion_error = 0;
		return (1);
	}
	return (0);
}

void	execute_ast(t_nodes *segment, char ***envp, int *exit_code)
{
	t_nodes	*ast;

	ast = ast_builder(segment);
	if (!scan_heredocs(ast))
		*exit_code = exec_tree(ast, envp);
	else
	{
		if (g_last_signal == 130)
			*exit_code = 130;
		else
			*exit_code = 1;
	}
	free_ast(ast);
}
