/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 06:07:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:12:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handle left parenthesis syntax rules.
 * @param tok Current left parenthesis token.
 * @param nxt Next token in the stream.
 * @param depth Pointer to the parenthesis depth counter.
 * @return 0 on success, or 2 on syntax error.
 */
int	syntax_handle_lparen(t_token *tok, t_token *nxt, int *depth)
{
	(void)tok;
	(*depth)++;
	if (nxt && (nxt->type == TOKEN_RPAREN || nxt->type == TOKEN_PIPE
			|| nxt->type == TOKEN_AND || nxt->type == TOKEN_OR
			|| nxt->type == TOKEN_SEMICOLON || nxt->type == TOKEN_BACKGROUND))
		return (print_syntax_error(nxt->value));
	return (0);
}

/**
 * @brief Handle right parenthesis syntax rules.
 * @param tok Current right parenthesis token.
 * @param nxt Next token in the stream.
 * @param depth Pointer to the parenthesis depth counter.
 * @return 0 on success, or 2 on syntax error.
 */
int	syntax_handle_rparen(t_token *tok, t_token *nxt, int *depth)
{
	(void)tok;
	(*depth)--;
	if (*depth < 0)
		return (print_syntax_error(")"));
	if (nxt && (nxt->type == TOKEN_WORD || nxt->type == TOKEN_LPAREN))
		return (print_syntax_error(nxt->value));
	return (0);
}

/**
 * @brief Handle pipe and logical operator syntax rules.
 * @param tok Current operator token.
 * @param nxt Next token or NULL.
 * @return 0 on success, or 2 on syntax error.
 */
int	syntax_handle_pipe_and_logic(t_token *tok, t_token *nxt)
{
	if (nxt && (nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
			|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON
			|| nxt->type == TOKEN_BACKGROUND || nxt->type == TOKEN_RPAREN))
		return (print_syntax_error(tok->value));
	return (0);
}

/**
 * @brief Handle semicolon and background operator syntax rules.
 * @param tok Current token.
 * @param nxt Next token or NULL.
 * @return 0 on success, or 2 on syntax error.
 */
int	syntax_handle_semicolon(t_token *tok, t_token *nxt)
{
	(void)tok;
	if (nxt && (nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
			|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON
			|| nxt->type == TOKEN_BACKGROUND))
		return (print_syntax_error(nxt->value));
	return (0);
}

/**
 * @brief Handle redirection operator syntax rules.
 * @param tok Current redirection token.
 * @param nxt Next token or NULL (expecting a word or assignment).
 * @return 0 on success, or 2 on syntax error.
 */
int	syntax_handle_redirection(t_token *tok, t_token *nxt)
{
	if (!tok->expanded && (!nxt || (nxt->type != TOKEN_WORD
				&& nxt->type != TOKEN_PREFIX)))
	{
		if (nxt)
			return (print_syntax_error(nxt->value));
		return (print_syntax_error("newline"));
	}
	return (0);
}
