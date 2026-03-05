/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:55:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_assignment_segment(t_nodes *segment)
{
	t_token	*first_tok;

	first_tok = (t_token *)segment->content;
	if (!first_tok || first_tok->type != TOKEN_WORD)
		return (0);
	return (ft_strchr(first_tok->value, '=') != NULL
		&& ft_strchr(first_tok->value, '=') != first_tok->value);
}

static void	extract_key_value(t_token *first_tok, char **key, char **val)
{
	char	*eq;

	eq = ft_strchr(first_tok->value, '=');
	*key = ft_substr(first_tok->value, 0, eq - first_tok->value);
	*val = ft_strdup(eq + 1);
}

static void	set_assignment(char *key, char *val, t_shell_state *state)
{
	ft_set_env(key, val, state);
	free(key);
	free(val);
	state->exit_code = 0;
}

int	try_handle_assignment_public(t_nodes *segment, t_shell_state *state)
{
	t_token	*first_tok;
	char	*key;
	char	*val;

	if (!is_assignment_segment(segment))
		return (0);
	first_tok = (t_token *)segment->content;
	if (!is_valid_ident(first_tok->value) || segment->next)
		return (0);
	extract_key_value(first_tok, &key, &val);
	set_assignment(key, val, state);
	ft_lstclear(&segment, del_token);
	return (1);
}
