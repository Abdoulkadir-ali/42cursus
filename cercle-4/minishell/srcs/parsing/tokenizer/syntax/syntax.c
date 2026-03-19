/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Ensure that the token list doesn't start with a forbidden operator.
 * @param tokens List of tokens for current scan.
 * @return Syntax error code or 0.
 */
static int	check_initial_token(t_nodes *tokens)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	tok = (t_token *)tokens->content;
	if (tok->type == TOKEN_PIPE || tok->type == TOKEN_SEMICOLON
		|| tok->type == TOKEN_AND || tok->type == TOKEN_OR
		|| tok->type == TOKEN_BACKGROUND)
		return (print_syntax_error(tok->value));
	return (0);
}

/**
 * @brief Orchestrate the full syntax pass on a list of tokens.
 * @param tokens Linked list of token nodes.
 * @return Syntax status (0 for OK, 2 for error).
 */
int	check_syntax(t_nodes *tokens)
{
	t_nodes	*curr;
	int		d;

	d = 0;
	if (check_initial_token(tokens))
		return (2);
	curr = tokens;
	while (curr)
	{
		if (process_node(curr, &d))
			return (2);
		curr = curr->next;
	}
	if (d != 0)
		return (print_syntax_error("newline"));
	return (0);
}
