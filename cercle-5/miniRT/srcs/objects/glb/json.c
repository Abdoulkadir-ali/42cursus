/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	process_type_string(char *ptr, t_accessor *acc)
{
	char	*t;
	int		j;

	j = 0;
	t = json_find_key(ptr, "type");
	if (!t)
		return ;
	while (*t && (*t == ':' || *t == ' ' || *t == '"'))
		t++;
	while (t[j] && t[j] != '"' && j < 15)
	{
		acc->type[j] = t[j];
		j++;
	}
	acc->type[j] = '\0';
}

void	glb_parse_accessor(char *json, int index, t_accessor *acc)
{
	char	*ptr;
	int		i;

	ptr = json_find_key(json, "accessors");
	if (!ptr)
		return ;
	ptr = ft_strchr(ptr, '[');
	i = 0;
	while (i < index && ptr)
	{
		ptr = ft_strchr(ptr, '}');
		if (ptr)
			ptr++;
		i++;
	}
	if (!ptr)
		return ;
	acc->buffer_view = json_get_int(ptr, "bufferView");
	acc->byte_offset = json_get_int(ptr, "byteOffset");
	if (acc->byte_offset < 0)
		acc->byte_offset = 0;
	acc->component_type = json_get_int(ptr, "componentType");
	acc->count = json_get_int(ptr, "count");
	process_type_string(ptr, acc);
}

void	glb_parse_buffer_view(char *json, int index, t_buffer_view *bv)
{
	char	*ptr;
	int		i;

	ptr = json_find_key(json, "bufferViews");
	if (!ptr)
		return ;
	ptr = ft_strchr(ptr, '[');
	i = 0;
	while (i < index && ptr)
	{
		ptr = ft_strchr(ptr, '}');
		if (ptr)
			ptr++;
		i++;
	}
	if (!ptr)
		return ;
	bv->buffer = json_get_int(ptr, "buffer");
	bv->byte_offset = json_get_int(ptr, "byteOffset");
	if (bv->byte_offset < 0)
		bv->byte_offset = 0;
	bv->byte_length = json_get_int(ptr, "byteLength");
	bv->byte_stride = json_get_int(ptr, "byteStride");
	if (bv->byte_stride <= 0)
		bv->byte_stride = 0;
}
