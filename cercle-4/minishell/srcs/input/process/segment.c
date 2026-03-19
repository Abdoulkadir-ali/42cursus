/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:55:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:38:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether a segment is a standalone assignment expression.
 * @param segment Token list representing one semicolon-delimited segment.
 * @return 1 when the first token is an assignment word, otherwise 0.
 */
static char	*is_assignment_segment(t_nodes *segment)
{
	t_token	*first_tok;
	char	*eq;

	first_tok = (t_token *)segment->content;
	if (!first_tok || first_tok->type != TOKEN_WORD)
		return (NULL);
	eq = ft_strchr(first_tok->value, '=');
	if (eq && eq != first_tok->value)
		return (eq);
	return (NULL);
}

/**
 * @brief Split an assignment token into key and value strings.
 * @param first_tok First token of the segment, expected to contain `=`.
 * @param key Output slot receiving the variable name.
 * @param val Output slot receiving the variable value.
 * @return This function does not return a value.
 */
static void	extract_key_value(t_token *first_tok, char *eq, char **key,
		char **val)
{
	*key = ft_substr(first_tok->value, 0, eq - first_tok->value);
	*val = ft_strdup(eq + 1);
}

/**
 * @brief Apply one parsed assignment to shell state and update status.
 * @param key Variable name extracted from the assignment token.
 * @param val Variable value extracted from the assignment token.
 * @param state Active shell state receiving the environment update.
 * @return This function does not return a value.
 */
static void	set_assignment(char *key, char *val, t_shell_state *state)
{
	ft_set_env(key, val, state);
	free(key);
	free(val);
	state->exit_code = 0;
}

/**
 * @brief Handle a segment as a direct variable assignment when possible.
 * @param segment Token list representing one semicolon-delimited segment.
 * @param state Active shell state receiving the environment update.
 * @return 1 when the segment is consumed as an assignment, otherwise 0.
 */
int	try_handle_assignment_public(t_nodes *segment, t_shell_state *state)
{
	t_token	*first_tok;
	char	*key;
	char	*val;
	char	*eq;

	eq = is_assignment_segment(segment);
	if (!eq)
		return (0);
	first_tok = (t_token *)segment->content;
	if (!is_valid_ident(first_tok->value) || segment->next)
		return (0);
	extract_key_value(first_tok, eq, &key, &val);
	set_assignment(key, val, state);
	ft_lstclear(&segment, del_token);
	return (1);
}
