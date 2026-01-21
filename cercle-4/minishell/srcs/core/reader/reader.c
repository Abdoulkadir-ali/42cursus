/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 05:59:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	*read_next_line_and_append(char *line, char quote)
{
	char		*prompt;
	char		*new_line;
	char		*temp;
	const char	*label;
	char		prompt_buf[16];

	label = ext_continuation_label(quote);
	if (label)
	{
		ft_bzero(prompt_buf, sizeof(prompt_buf));
		ft_strlcpy(prompt_buf, label, sizeof(prompt_buf));
		ft_strlcat(prompt_buf, "> ", sizeof(prompt_buf));
		prompt = prompt_buf;
	}
	else
		prompt = get_prompt(0);
	new_line = read_input(prompt);
	if (!new_line)
	{
		ft_puterror("unexpected EOF while looking for matching `%c'\n", quote);
		free(line);
		return (NULL);
	}
	temp = append_line(line, new_line);
	free(line);
	free(new_line);
	return (temp);
}

static char	check_unclosed_quote(char *str)
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

static char	*handle_multiline_input(char *line)
{
	char	quote;
	char	code;

	quote = check_unclosed_quote(line);
	while (quote)
	{
		line = read_next_line_and_append(line, quote);
		if (!line)
			return (NULL);
		quote = check_unclosed_quote(line);
	}
	/* Continue reading if line ends with a known continuation operator. */
	while (1)
	{
		if (ext_check_paren_depth(line) > 0)
		{
			line = read_next_line_and_append(line, 'p');
			if (!line)
				return (NULL);
			continue ;
		}
		code = ext_detect_trailing_op(line);
		if (code == 0)
			break ;
		line = read_next_line_and_append(line, code);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_command_line(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(1);
	line = read_input(prompt);
	if (!line)
		return (NULL);
	return (handle_multiline_input(line));
}
