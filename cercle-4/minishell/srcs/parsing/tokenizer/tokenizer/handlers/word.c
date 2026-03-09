/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Extract the next quoted or unquoted chunk of a shell word.
 * @param str Address of the scan cursor in the input string.
 * @param quoted Output flag set when the chunk came from quotes.
 * @return Newly allocated chunk string, or NULL on failure.
 */
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

/**
 * @brief Skip the literal dollar in `$'` and `$"` word prefixes.
 * @param str Address of the scan cursor in the input string.
 * @return 1 when the prefix was consumed, otherwise 0.
 */
static int	skip_dollar_quote(char **str)
{
	if (**str == '$' && ((*str)[1] == '"' || (*str)[1] == '\''))
	{
		(*str)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Concatenate one chunk onto the growing word buffer.
 * @param acc Accumulated word string.
 * @param chunk Newly allocated chunk to append.
 * @return Newly allocated concatenated string.
 */
static char	*append_and_free(char *acc, char *chunk)
{
	char	*tmp;

	tmp = ft_strjoin(acc, chunk);
	free(acc);
	free(chunk);
	return (tmp);
}

/**
 * @brief Collect every chunk that belongs to the next shell word token.
 * @param str Address of the scan cursor in the input string.
 * @param quoted Output flag describing whether quotes were encountered.
 * @return Newly allocated full word string, or NULL on failure.
 */
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

/**
 * @brief Tokenize one shell word from the current scan position.
 * @param str Address of the scan cursor in the input string.
 * @return Newly allocated word token, or NULL on failure.
 */
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
