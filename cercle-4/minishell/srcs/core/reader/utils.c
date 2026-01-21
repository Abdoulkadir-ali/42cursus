/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 06:02:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*append_line(char *line, char *new_line)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(line, "\n");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, new_line);
	free(temp);
	return (result);
}

char	*get_prompt(int is_initial)
{
	if (!isatty(STDIN_FILENO))
		return (NULL);
	if (is_initial)
		return ("minishell> ");
	return ("> ");
}

char	*read_input(char *prompt)
{
	char	*buf;
	int		i;
	char	c;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	buf = ft_calloc(10000, 1);
	i = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		if (i >= 9999)
			break ;
	}
	if (i > 0)
	{
		if (buf[i - 1] == '\n')
			buf[i - 1] = '\0';
		return (buf);
	}
	free(buf);
	return (NULL);
}

char	*last_non_space(char *s)
{
	char	*p;

	if (!s || !*s)
		return (NULL);
	p = s + ft_strlen(s) - 1;
	while (p >= s && ft_isspace(*p))
		p--;
	if (p < s)
		return (NULL);
	return (p);
}

char	check_unclosed_quote(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (quote == 0)
		{
			if (*str == '\'' || *str == '"')
				quote = *str;
		}
		else
		{
			if (*str == quote)
				quote = 0;
		}
		str++;
	}
	return (quote);
}
