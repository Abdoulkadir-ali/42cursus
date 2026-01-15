/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:31:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	handle_semicolon(char **str, t_token *token)
{
	token->type = TOKEN_SEMICOLON;
	token->value = ft_strldup(*str, 1);
	(*str)++;
	return (token->value == NULL);
}
