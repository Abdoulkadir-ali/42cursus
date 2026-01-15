/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:25:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	handle_red_in(char **str, t_token *token)
{
	if (*(*str + 1) == '<')
	{
		token->type = TOKEN_HEREDOC;
		token->value = ft_strldup(*str, 2);
		(*str) += 2;
	}
	else
	{
		token->type = TOKEN_RED_IN;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	return (token->value == NULL);
}
