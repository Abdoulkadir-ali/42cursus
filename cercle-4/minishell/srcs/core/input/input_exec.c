/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:51:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:58:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	execute_command(t_nodes *tokens, char ***envp, int *exit_code)
{
	t_nodes	*ast;

	ast = ast_builder(tokens);
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

int	process_segment_local(t_nodes *segment, char ***envp, int *exit_code)
{
	expand_tokens(&segment, *envp, *exit_code);
	if (g_expansion_error)
	{
		*exit_code = g_exit_code;
		ft_lstclear(&segment, del_token);
		g_expansion_error = 0;
		return (1);
	}
	execute_command(segment, envp, exit_code);
	return (0);
}