/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_object_member(t_json_value *val, const char **s)
{
	char	*key;

	json_skip_ws(s);
	key = json_parse_inner_string(s);
	if (!key)
		return (0);
	json_skip_ws(s);
	if (**s == ':')
		(*s)++;
	json_hash_insert(&val->object, key, json_parse_inner_value(s));
	json_skip_ws(s);
	if (**s == ',')
		(*s)++;
	return (1);
}

t_json_value	*json_parse_inner_object(const char **s)
{
	t_json_value	*val;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_OBJECT;
	(*s)++;
	while (**s && **s != '}')
	{
		if (!parse_object_member(val, s))
			break ;
	}
	if (**s == '}')
		(*s)++;
	return (val);
}

static void	parse_array_elem(t_json_value *val, const char **s)
{
	t_json_value	*elem;
	size_t			new_cap;

	elem = json_parse_inner_value(s);
	if (elem)
	{
		if (val->array.count >= val->array.cap)
		{
			if (val->array.cap == 0)
				new_cap = 8;
			else
				new_cap = val->array.cap * 2;
			val->array.elements = json_realloc(val->array.elements,
					sizeof(t_json_value *) * val->array.cap,
					sizeof(t_json_value *) * new_cap);
			val->array.cap = new_cap;
		}
		val->array.elements[val->array.count++] = elem;
	}
	json_skip_ws(s);
	if (**s == ',')
		(*s)++;
}

t_json_value	*json_parse_inner_array(const char **s)
{
	t_json_value	*val;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_ARRAY;
	(*s)++;
	while (**s && **s != ']')
		parse_array_elem(val, s);
	if (**s == ']')
		(*s)++;
	return (val);
}
