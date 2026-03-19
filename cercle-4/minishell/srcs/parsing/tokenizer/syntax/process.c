/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 06:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Dispatch logic to specific syntax rules based on the token type.
 * @param tok Token to process.
 * @param nxt Next token in the stream, or NULL.
 * @param d Parenthesis depth pointer.
 * @return Syntax error code, or 0 when rules are satisfied.
 */
int	process_rules(t_token *tok, t_token *nxt, int *d)
{
	if (tok->type == TOKEN_LPAREN)
		return (syntax_handle_lparen(tok, nxt, d));
	if (tok->type == TOKEN_RPAREN)
		return (syntax_handle_rparen(tok, nxt, d));
	if (tok->type == TOKEN_PIPE || tok->type == TOKEN_AND
		|| tok->type == TOKEN_OR)
		return (syntax_handle_pipe_and_logic(tok, nxt));
	if (tok->type == TOKEN_SEMICOLON || tok->type == TOKEN_BACKGROUND)
		return (syntax_handle_semicolon(tok, nxt));
	if (is_redirection(tok->type))
		return (syntax_handle_redirection(tok, nxt));
	return (0);
}

/**
 * @brief Dispatch for one token-node in the linked list.
 * @param curr Head of the current token-node to check.
 * @param d Parenthesis depth pointer to maintain during the scan.
 * @return 0 on success, shell error code otherwise.
 */
int	process_node(t_nodes *curr, int *d)
{
	t_token	*tok;
	t_token	*nxt;

	tok = (t_token *)curr->content;
	nxt = NULL;
	if (curr->next)
		nxt = (t_token *)curr->next->content;
	return (process_rules(tok, nxt, d));
}
