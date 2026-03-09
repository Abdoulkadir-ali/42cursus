/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Allocate a fresh token object for separator tokenization.
 * @return Newly allocated token object, or NULL on allocation failure.
 */
static t_token	*alloc_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quoted = 0;
	token->expanded = 0;
	token->value = NULL;
	return (token);
}

/**
 * @brief Dispatch separator tokenization based on the current input character.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by the selected handler.
 * @return 0 on success, non-zero on failure or unknown separator.
 */
static int	dispatch_separator(char **str, t_token *token)
{
	if (**str == '|')
		return (handle_pipe(str, token));
	if (**str == '(')
		return (handle_paren(str, token, 1));
	if (**str == ')')
		return (handle_paren(str, token, 0));
	if (**str == '&')
		return (handle_ampersand(str, token));
	if (**str == '<')
		return (handle_red_in(str, token));
	if (**str == '>')
		return (handle_red_out(str, token));
	if (**str == ';')
		return (handle_semicolon(str, token));
	return (1);
}

/**
 * @brief Tokenize one separator or operator from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @return Newly allocated token, or NULL on failure.
 */
t_token	*handle_separator(char **str)
{
	t_token	*token;
	int		rc;

	if (!str || !*str || !**str)
		return (NULL);
	token = alloc_token();
	if (!token)
		return (NULL);
	rc = dispatch_separator(str, token);
	if (rc != 0)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	return (token);
}
