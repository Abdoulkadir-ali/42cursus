/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:25:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:25:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

static const char	*json_skip_string(const char *p, const char *end)
{
	p++;
	while (p < end)
	{
		if (*p == '\\' && p + 1 < end)
			p++;
		else if (*p == '"')
		{
			p++;
			break ;
		}
		p++;
	}
	return (p);
}

static const char	*json_skip_braces(const char *p, const char *end)
{
	int		depth;
	int		in_str;

	depth = 1;
	in_str = 0;
	p++;
	while (p < end && depth > 0)
	{
		if (in_str)
		{
			if (*p == '\\' && p + 1 < end)
				p++;
			else if (*p == '"')
				in_str = 0;
		}
		else if (*p == '"')
			in_str = 1;
		else if (*p == '{' || *p == '[')
			depth++;
		else if (*p == '}' || *p == ']')
			depth--;
		p++;
	}
	return (p);
}

const char	*json_skip_value(const char *p, const char *end)
{
	p = json_skip_ws(p, end);
	if (p >= end)
		return (p);
	if (*p == '{' || *p == '[')
		return (json_skip_braces(p, end));
	if (*p == '"')
		return (json_skip_string(p, end));
	while (p < end && *p != ',' && *p != '}' && *p != ']'
		&& *p != ' ' && *p != '\n' && *p != '\t' && *p != '\r')
		p++;
	return (p);
}
