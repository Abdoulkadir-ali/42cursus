/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Tokenize `|` or `||` from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_pipe(char **str, t_token *token)
{
	if (*(*str + 1) == '|')
	{
		token->type = TOKEN_OR;
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else
	{
		token->type = TOKEN_PIPE;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}

/**
 * @brief Tokenize one parenthesis from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @param left Non-zero for `(`, zero for `)`.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_paren(char **str, t_token *token, int left)
{
	if (left)
		token->type = TOKEN_LPAREN;
	else
		token->type = TOKEN_RPAREN;
	token->value = ft_strldup(*str, 1);
	(*str)++;
	return (token->value == NULL);
}

/**
 * @brief Tokenize `&` or `&&` from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_ampersand(char **str, t_token *token)
{
	if (*(*str + 1) == '&')
	{
		token->type = TOKEN_AND;
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else
	{
		token->type = TOKEN_WORD;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}

/**
 * @brief Tokenize `<`, `<<`, or `<<<` from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_red_in(char **str, t_token *token)
{
	if (*(*str + 1) == '<')
	{
		if (*(*str + 2) == '<')
		{
			token->type = TOKEN_HERESTR;
			token->value = ft_strldup(*str, 3);
			(*str) += 3;
		}
		else
		{
			token->type = TOKEN_HEREDOC;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
	}
	else
	{
		token->type = TOKEN_RED_IN;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}
