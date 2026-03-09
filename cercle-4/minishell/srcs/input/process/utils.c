/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:38:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether an input line contains only whitespace.
 * @param str Raw input line.
 * @return 1 when the line is empty after whitespace filtering, else 0.
 */
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

/**
 * @brief Expand a segment and abort it if expansion reported an error.
 * @param segment Address of the segment token list to expand or clear.
 * @param state Active shell state providing env and exit status.
 * @param new_exit_code Output slot receiving the preserved exit code.
 * @return 1 when the segment is discarded, otherwise 0.
 */
int	expand_and_check_error(t_nodes **segment, t_shell_state *state,
		int *new_exit_code)
{
	if (expand_tokens(segment, state->envp, state->exit_code))
		state->expansion_error = 1;
	if (state->expansion_error)
	{
		*new_exit_code = state->exit_code;
		ft_lstclear(segment, del_token);
		state->expansion_error = 0;
		return (1);
	}
	return (0);
}

/**
 * @brief Build an AST for one segment, prepare heredocs, and execute it.
 * @param segment Token list representing one semicolon-delimited segment.
 * @param state Active shell state used during AST execution.
 * @return This function does not return a value.
 */
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

/**
 * @brief Detach tokens from the current cursor until a semicolon is reached.
 * @param segment Output slot receiving the extracted segment head.
 * @param seg_tail Output slot receiving the extracted segment tail.
 * @param it Cursor advanced to the semicolon or stream end.
 * @return This function does not return a value.
 */
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

/**
 * @brief Remove one semicolon token and expose the next segment cursor.
 * @param it Current token node after segment extraction.
 * @param pnext Output slot receiving the next segment start.
 * @return This function does not return a value.
 */
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
