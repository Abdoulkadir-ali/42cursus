/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Tokenize `>`, `>>`, or `>|` from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_red_out(char **str, t_token *token)
{
	if (*(*str + 1) == '>')
	{
		token->type = TOKEN_APPEND;
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else if (*(*str + 1) == '|')
	{
		token->type = TOKEN_RED_OUT;
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else
	{
		token->type = TOKEN_RED_OUT;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}

/**
 * @brief Tokenize `;` or `;;` from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @param token Token object populated by this handler.
 * @return Non-zero on allocation failure, otherwise 0.
 */
int	handle_semicolon(char **str, t_token *token)
{
	token->type = TOKEN_SEMICOLON;
	if (*(*str + 1) == ';')
	{
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else
	{
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}
