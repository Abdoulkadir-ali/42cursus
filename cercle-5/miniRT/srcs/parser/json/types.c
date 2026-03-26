/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*json_parse_inner_string(const char **s)
{
	const char	*start;
	char		*str;

	if (**s != '"')
		return (NULL);
	(*s)++;
	start = *s;
	while (**s && **s != '"')
	{
		if (**s == '\\' && (*s)[1])
			(*s)++;
		(*s)++;
	}
	str = ft_substr(start, 0, *s - start);
	if (**s == '"')
		(*s)++;
	return (str);
}

t_json_value	*json_parse_inner_number(const char **s)
{
	t_json_value	*val;
	char			*end;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_NUMBER;
	val->number = strtod(*s, &end);
	*s = end;
	return (val);
}
