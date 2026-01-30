/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:01:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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

static char	*read_function_input(char *prompt, t_shell_state *state)
{
	char	*new_line;

	new_line = read_input(prompt, state);
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

char	*read_function_body(char *line, size_t n, t_shell_state *state)
{
	char	*prompt;
	char	*new_line;
	char	*res;

	prompt = build_function_prompt(n);
	if (!prompt)
		return (free(line), NULL);
	free(line);
	new_line = read_function_input(prompt, state);
	if (!new_line)
		return (NULL);
	res = format_function_body(new_line);
	return (res);
}
