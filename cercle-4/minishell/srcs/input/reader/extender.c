/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 23:55:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	check_pairs_state(char *s)
{
	int		depth;
	char	quote;

	depth = 0;
	quote = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (quote != '\'' && *s == '\\')
		{
			s++;
			if (*s)
				s++;
			continue ;
		}
		if (quote == 0 && (*s == '\'' || *s == '"'))
			quote = *s;
		else if (quote == 0 && *s == '(')
			depth++;
		else if (quote == 0 && *s == ')')
			depth--;
		else if (quote != 0 && *s == quote)
			quote = 0;
		s++;
	}
	if (quote != 0)
		return (quote);
	if (depth > 0)
		return ('p');
	return (0);
}

static int	handle_escape(char *line, char *p)
{
	int	count;

	count = 0;
	while (p >= line && *p == '\\')
	{
		count++;
		p--;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

static char	check_trailing_op(char *line, t_op_def *ops)
{
	char	*p;
	int		i;
	size_t	len;

	p = line + ft_strlen(line) - 1;
	while (p >= line && ft_isspace(*p))
		p--;
	if (p < line)
		return (0);
	if (*p == '\\' && handle_escape(line, p))
		return ('\\');
	i = 0;
	while (ops[i].code)
	{
		len = ft_strlen(ops[i].symbol);
		if (ops[i].counterpart == 0 && ops[i].code != '\\' && p - (len
				- 1) >= line && ft_strncmp(p - (len - 1), ops[i].symbol,
				len) == 0)
			return (ops[i].code);
		i++;
	}
	return (0);
}

char	ext_analyze_input(char *line)
{
	char		state_code;
	t_op_def	*ops;

	ops = get_ops();
	state_code = check_pairs_state(line);
	if (state_code != 0)
		return (state_code);
	return (check_trailing_op(line, ops));
}
