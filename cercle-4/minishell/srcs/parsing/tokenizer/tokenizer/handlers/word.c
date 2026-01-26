/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/25 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_chunk(char **str, int *quoted)
{
	char	*chunk;
	int		len;
	char	quote;

	*quoted = 0;
	if (**str == '\'' || **str == '"')
	{
		quote = **str;
		*quoted = 1;
		len = scan_quoted(*str, quote);
		if (len < 0)
		{
			ft_puterror("syntax error: unclosed quote\n");
			return (NULL);
		}
	}
	else
		len = scan_unquoted(*str);
	chunk = ft_substr(*str, 0, len);
	*str += len;
	return (chunk);
}

static int	skip_dollar_quote(char **str)
{
	if (**str == '$' && ((*str)[1] == '"' || (*str)[1] == '\''))
	{
		(*str)++;
		return (1);
	}
	return (0);
}

static char	*append_and_free(char *acc, char *chunk)
{
	char	*tmp;

	tmp = ft_strjoin(acc, chunk);
	free(acc);
	free(chunk);
	return (tmp);
}

static char	*collect_word(char **str, int *quoted)
{
	char	*acc;
	char	*chunk;

	acc = ft_strdup("");
	if (!acc)
		return (NULL);
	*quoted = 0;
	while (**str)
	{
		if (ft_isspace(**str) || ft_strchr("|<>()&", **str) || **str == ';')
			break ;
		if (skip_dollar_quote(str))
			continue ;
		chunk = get_chunk(str, quoted);
		if (!chunk)
			return (free(acc), NULL);
		acc = append_and_free(acc, chunk);
		if (!acc)
			return (NULL);
	}
	return (acc);
}

t_token	*handle_word(char **str)
{
	t_token	*token;
	char	*acc;
	int		quoted;

	acc = collect_word(str, &quoted);
	if (!acc)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(acc), NULL);
	token->type = TOKEN_WORD;
	token->value = acc;
	token->quoted = quoted;
	token->expanded = 0;
	return (token);
}
