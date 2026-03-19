/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 07:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether the accumulated word is an unquoted assignment prefix.
 * @param s Candidate string to inspect.
 * @return true if it is a valid prefix, otherwise false.
 */
bool	is_assignment_prefix(const char *s)
{
	char	*eq;
	size_t	i;

	if (!s || !*s)
		return (false);
	eq = ft_strchr((char *)s, '=');
	if (!eq || eq == s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (false);
	i = 1;
	while (&s[i] < (const char *)eq)
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Extract one chunk from the input: 
 * either a quoted chunk or unquoted run.
 * @param str Address of the scan cursor.
 * @param quoted Set to true if chunk originated from quotes.
 * @return Newly allocated chunk string, or NULL on failure.
 */
char	*get_chunk(char **str, bool *quoted)
{
	char	*chunk;
	int		len;
	char	quote;

	*quoted = false;
	if (**str == '\'' || **str == '"')
	{
		quote = **str;
		*quoted = true;
		len = scan_quoted(*str, quote);
		if (len < 0)
			return (ft_puterror("syntax error: unclosed quote\n"), NULL);
	}
	else
		len = scan_unquoted(*str);
	chunk = ft_substr(*str, 0, (size_t)len);
	*str += len;
	return (chunk);
}

/**
 * @brief Consume a literal dollar that prefixes a quote (e.g. $' or $").
 * @param str Address of the scan cursor.
 * @return true when consumed, false otherwise.
 */
bool	skip_dollar_quote(char **str)
{
	if (**str == '$' && ((*str)[1] == '"' || (*str)[1] == '\''))
	{
		(*str)++;
		return (true);
	}
	return (false);
}

/**
 * @brief Inner loop for collecting word chunks until a separator or space.
 * @param str Address of the scan cursor.
 * @param quoted Pointer to boolean to accumulate quoted state.
 * @param acc Accumulated string so far.
 * @return Final word string or NULL on failure.
 */
char	*collect_word_loop(char **str, bool *quoted, char *acc)
{
	char	*chunk;
	char	*tmp;
	bool	q;

	while (**str)
	{
		if (ft_isspace(**str) || ft_strchr("|<>()&", **str) || **str == ';')
			break ;
		if (skip_dollar_quote(str))
			continue ;
		chunk = get_chunk(str, &q);
		if (!chunk)
			return (free(acc), NULL);
		if (q)
			*quoted = true;
		tmp = ft_strjoin(acc, chunk);
		free(acc);
		free(chunk);
		if (!tmp)
			return (NULL);
		acc = tmp;
	}
	return (acc);
}
