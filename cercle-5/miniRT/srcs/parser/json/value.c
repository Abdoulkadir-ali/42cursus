/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_json_value	*json_parse_string_val(const char **s)
{
	t_json_value	*v;

	v = ft_calloc(1, sizeof(t_json_value));
	if (!v)
		return (NULL);
	v->type = JSON_STRING;
	v->string = json_parse_inner_string(s);
	return (v);
}

static t_json_value	*json_parse_bool_val(const char **s, bool b, int len)
{
	t_json_value	*v;

	v = ft_calloc(1, sizeof(t_json_value));
	if (!v)
		return (NULL);
	v->type = JSON_BOOL;
	v->boolean = b;
	*s += len;
	return (v);
}

static t_json_value	*json_parse_null_val(const char **s)
{
	t_json_value	*v;

	v = ft_calloc(1, sizeof(t_json_value));
	if (!v)
		return (NULL);
	v->type = JSON_NULL;
	*s += 4;
	return (v);
}

t_json_value	*json_parse_inner_value(const char **s)
{
	json_skip_ws(s);
	if (**s == '{')
		return (json_parse_inner_object(s));
	if (**s == '[')
		return (json_parse_inner_array(s));
	if (**s == '"')
		return (json_parse_string_val(s));
	if (ft_isdigit(**s) || **s == '-')
		return (json_parse_inner_number(s));
	if (ft_strncmp(*s, "true", 4) == 0)
		return (json_parse_bool_val(s, true, 4));
	if (ft_strncmp(*s, "false", 5) == 0)
		return (json_parse_bool_val(s, false, 5));
	if (ft_strncmp(*s, "null", 4) == 0)
		return (json_parse_null_val(s));
	return (NULL);
}
