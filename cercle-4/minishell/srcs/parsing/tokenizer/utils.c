/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:04:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 04:58:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	print_syntax_error(char *token)
{
	ft_puterror("syntax error near unexpected token `%s'\n", token);
	return (2);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_RED_IN || type == TOKEN_RED_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC
		|| type == TOKEN_HERESTR);
}
