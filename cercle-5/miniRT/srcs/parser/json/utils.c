/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	json_skip_ws(const char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

size_t	json_hash_key(const char *key, size_t size)
{
	size_t	h;

	h = 5381;
	while (*key)
		h = ((h << 5) + h) + *key++;
	return (h % size);
}

void	*json_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void	json_hash_insert(t_json_object *obj, char *key, t_json_value *val)
{
	size_t				idx;
	t_json_hash_entry	*entry;

	if (obj->hash_size == 0)
	{
		obj->hash_size = 31;
		obj->hashmap = ft_calloc(obj->hash_size, sizeof(t_json_hash_entry *));
	}
	idx = json_hash_key(key, obj->hash_size);
	entry = malloc(sizeof(t_json_hash_entry));
	if (!entry)
		return ;
	entry->key = key;
	entry->value = val;
	entry->next = obj->hashmap[idx];
	obj->hashmap[idx] = entry;
}
