/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 04:11:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static size_t	count_paren_pairs(const char *s)
{
	size_t	i;
	size_t	n;
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	n = 0;
	while (i < len && s[i] == '(')
	{
		n++;
		i++;
	}
	if (n == 0)
		return (0);
	while (i < len && s[i] == ')')
		i++;
	if (i != len)
		return (0);
	if (len != n * 2)
		return (0);
	return (n);
}

static char	*build_function_prompt(size_t n)
{
	char	*prompt;
	size_t	p_len;
	size_t	i;

	p_len = n * (sizeof("function ") - 1) + 3;
	prompt = malloc(p_len);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	i = 0;
	while (i < n)
	{
		ft_strlcat(prompt, "function ", p_len);
		i++;
	}
	ft_strlcat(prompt, "> ", p_len);
	return (prompt);
}

static char	*read_function_input(char *prompt)
{
	char	*new_line;

	new_line = read_input(prompt);
	free(prompt);
	if (!new_line)
	{
		ft_puterror("syntax error: unexpected end of file\n");
		return (NULL);
	}
	return (new_line);
}

static char	*format_function_body(char *new_line)
{
	char	*res;
	size_t	len;

	len = ft_strlen(new_line);
	res = malloc(len + 3);
	if (!res)
	{
		free(new_line);
		return (NULL);
	}
	snprintf(res, len + 3, "(%s)", new_line);
	free(new_line);
	return (res);
}

static char	*read_function_body(char *line, size_t n)
{
	char	*prompt;
	char	*new_line;
	char	*res;

	prompt = build_function_prompt(n);
	if (!prompt)
		return (free(line), NULL);
	free(line);
	new_line = read_function_input(prompt);
	if (!new_line)
		return (NULL);
	res = format_function_body(new_line);
	return (res);
}

char	*handle_parenthesis(char *line, char *trimmed)
{
	size_t	pairs;

	if (!trimmed)
		return (NULL);
	pairs = count_paren_pairs(trimmed);
	if (pairs > 0)
	{
		free(trimmed);
		line = read_function_body(line, pairs);
		return (line);
	}
	if (ft_strcmp(trimmed, "()") == 0)
	{
		free(trimmed);
		line = read_function_body(line, 1);
		return (line);
	}
	free(trimmed);
	return (NULL);
}
