/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_json_value	*json_parse(const char *json_str)
{
	const char	*s;

	s = json_str;
	return (json_parse_inner_value(&s));
}

t_json_value	*json_get(t_json_value *val, const char *key)
{
	size_t				idx;
	t_json_hash_entry	*entry;

	if (!val || val->type != JSON_OBJECT || !val->u.object.hashmap)
		return (NULL);
	idx = json_hash_key(key, val->u.object.hash_size);
	entry = val->u.object.hashmap[idx];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}

t_json_value	*json_at(t_json_value *val, size_t index)
{
	if (!val || val->type != JSON_ARRAY || index >= val->u.array.count)
		return (NULL);
	return (val->u.array.elements[index]);
}

int	json_get_int(t_json_value *obj, const char *key)
{
	t_json_value	*val;

	val = json_get(obj, key);
	if (!val || val->type != JSON_NUMBER)
		return (-1);
	return ((int)val->u.number);
}
