/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	json_free_array(t_json_value *val)
{
	size_t	i;

	i = 0;
	while (i < val->array.count)
	{
		json_free(val->array.elements[i]);
		i++;
	}
	if (val->array.elements)
		free(val->array.elements);
}

static void	json_free_object(t_json_value *val)
{
	size_t				i;
	t_json_hash_entry	*entry;
	t_json_hash_entry	*next;

	i = 0;
	if (val->object.hashmap)
	{
		while (i < val->object.hash_size)
		{
			entry = val->object.hashmap[i++];
			while (entry)
			{
				next = entry->next;
				free(entry->key);
				json_free(entry->value);
				free(entry);
				entry = next;
			}
		}
		free(val->object.hashmap);
	}
}

void	json_free(t_json_value *val)
{
	if (!val)
		return ;
	if (val->type == JSON_STRING)
		free(val->string);
	else if (val->type == JSON_ARRAY)
		json_free_array(val);
	else if (val->type == JSON_OBJECT)
		json_free_object(val);
	free(val);
}
