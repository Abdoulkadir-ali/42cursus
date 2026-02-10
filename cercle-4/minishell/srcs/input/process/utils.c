/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:12:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_whitespace_only(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	expand_and_check_error(t_nodes **segment, t_shell_state *state,
		int *new_exit_code)
{
	expand_tokens(segment, state->envp, state->exit_code);
	if (state->expansion_error)
	{
		*new_exit_code = state->exit_code;
		ft_lstclear(segment, del_token);
		state->expansion_error = 0;
		return (1);
	}
	return (0);
}

void	execute_ast(t_nodes *segment, t_shell_state *state)
{
	t_ast	*ast;

	ast = ast_builder(segment);
	if (!scan_heredocs(ast, state))
		state->exit_code = exec_tree(ast, state);
	else
	{
		if (g_last_signal == 130)
			state->exit_code = 130;
		else
			state->exit_code = 1;
	}
	free_ast(ast);
}

void	build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
		t_nodes **it)
{
	t_nodes	*next;

	while (*it && ((t_token *)(*it)->content)->type != TOKEN_SEMICOLON)
	{
		next = (*it)->next;
		(*it)->next = NULL;
		if (!*segment)
			*segment = *it;
		else
			(*seg_tail)->next = *it;
		*seg_tail = *it;
		*it = next;
	}
}

void	consume_semicolon_if_present(t_nodes *it, t_nodes **pnext)
{
	if (it && ((t_token *)it->content)->type == TOKEN_SEMICOLON)
	{
		*pnext = it->next;
		del_token(it->content);
		free(it);
	}
	else
		*pnext = it;
}
