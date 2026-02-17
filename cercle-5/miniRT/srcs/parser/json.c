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

static void	skip_ws(const char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

static size_t	hash_key(const char *key, size_t size)
{
	size_t	h;

	h = 5381;
	while (*key)
		h = ((h << 5) + h) + *key++;
	return (h % size);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

static void	json_hash_insert(t_json_object *obj, char *key, t_json_value *val)
{
	size_t				idx;
	t_json_hash_entry	*entry;

	if (obj->hash_size == 0)
	{
		obj->hash_size = 31;
		obj->hashmap = ft_calloc(obj->hash_size, sizeof(t_json_hash_entry *));
	}
	idx = hash_key(key, obj->hash_size);
	entry = malloc(sizeof(t_json_hash_entry));
	if (!entry)
		return ;
	entry->key = key;
	entry->value = val;
	entry->next = obj->hashmap[idx];
	obj->hashmap[idx] = entry;
}

static t_json_value	*json_parse_inner_value(const char **s);

static char	*json_parse_inner_string(const char **s)
{
	const char	*start;
	char		*str;
	size_t		len;

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
	len = *s - start;
	str = ft_substr(start, 0, len);
	if (**s == '"')
		(*s)++;
	return (str);
}

static t_json_value	*json_parse_inner_object(const char **s)
{
	t_json_value	*val;
	char			*key;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_OBJECT;
	(*s)++;
	while (**s && **s != '}')
	{
		skip_ws(s);
		key = json_parse_inner_string(s);
		if (!key)
			break ;
		skip_ws(s);
		if (**s == ':')
			(*s)++;
		json_hash_insert(&val->u.object, key, json_parse_inner_value(s));
		skip_ws(s);
		if (**s == ',')
			(*s)++;
	}
	if (**s == '}')
		(*s)++;
	return (val);
}

static t_json_value	*json_parse_inner_array(const char **s)
{
	t_json_value	*val;
	t_json_value	*elem;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_ARRAY;
	(*s)++;
	while (**s && **s != ']')
	{
		elem = json_parse_inner_value(s);
		if (elem)
		{
			val->u.array.elements = ft_realloc(val->u.array.elements,
				sizeof(t_json_value *) * val->u.array.count,
				sizeof(t_json_value *) * (val->u.array.count + 1));
			val->u.array.elements[val->u.array.count++] = elem;
		}
		skip_ws(s);
		if (**s == ',')
			(*s)++;
	}
	if (**s == ']')
		(*s)++;
	return (val);
}

static t_json_value	*json_parse_inner_number(const char **s)
{
	t_json_value	*val;
	char			*end;

	val = ft_calloc(1, sizeof(t_json_value));
	if (!val)
		return (NULL);
	val->type = JSON_NUMBER;
	val->u.number = strtod(*s, &end);
	*s = end;
	return (val);
}

static t_json_value	*json_parse_inner_value(const char **s)
{
	skip_ws(s);
	if (**s == '{')
		return (json_parse_inner_object(s));
	if (**s == '[')
		return (json_parse_inner_array(s));
	if (**s == '"')
	{
		t_json_value *v = ft_calloc(1, sizeof(t_json_value));
		v->type = JSON_STRING;
		v->u.string = json_parse_inner_string(s);
		return (v);
	}
	if (ft_isdigit(**s) || **s == '-')
		return (json_parse_inner_number(s));
	if (ft_strncmp(*s, "true", 4) == 0)
	{
		t_json_value *v = ft_calloc(1, sizeof(t_json_value));
		v->type = JSON_BOOL;
		v->u.boolean = true;
		*s += 4;
		return (v);
	}
	if (ft_strncmp(*s, "false", 5) == 0)
	{
		t_json_value *v = ft_calloc(1, sizeof(t_json_value));
		v->type = JSON_BOOL;
		v->u.boolean = false;
		*s += 5;
		return (v);
	}
	if (ft_strncmp(*s, "null", 4) == 0)
	{
		t_json_value *v = ft_calloc(1, sizeof(t_json_value));
		v->type = JSON_NULL;
		*s += 4;
		return (v);
	}
	return (NULL);
}

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
	idx = hash_key(key, val->u.object.hash_size);
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

double	json_as_number(t_json_value *val)
{
	if (!val || val->type != JSON_NUMBER)
		return (0.0);
	return (val->u.number);
}

const char	*json_as_string(t_json_value *val)
{
	if (!val || val->type != JSON_STRING)
		return (NULL);
	return (val->u.string);
}

void	json_free(t_json_value *val)
{
	size_t				i;
	t_json_hash_entry	*entry;
	t_json_hash_entry	*next;

	if (!val)
		return ;
	if (val->type == JSON_STRING)
		free(val->u.string);
	else if (val->type == JSON_ARRAY)
	{
		i = 0;
		while (i < val->u.array.count)
			json_free(val->u.array.elements[i++]);
		if (val->u.array.elements)
			free(val->u.array.elements);
	}
	else if (val->type == JSON_OBJECT)
	{
		i = 0;
		if (val->u.object.hashmap)
		{
			while (i < val->u.object.hash_size)
			{
				entry = val->u.object.hashmap[i++];
				while (entry)
				{
					next = entry->next;
					free(entry->key);
					json_free(entry->value);
					free(entry);
					entry = next;
				}
			}
			free(val->u.object.hashmap);
		}
	}
	free(val);
}
