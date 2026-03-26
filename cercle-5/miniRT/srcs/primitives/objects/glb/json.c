/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	glb_parse_accessor(t_json_value *json, int index, t_accessor *acc)
{
	t_json_value	*accessors;
	t_json_value	*a;
	const char		*type;

	ft_memset(acc, 0, sizeof(t_accessor));
	accessors = json_get(json, "accessors");
	a = json_at(accessors, index);
	if (!a)
		return ;
	acc->buffer_view = json_get_int(a, "bufferView");
	acc->byte_offset = json_get_int(a, "byteOffset");
	if (acc->byte_offset < 0)
		acc->byte_offset = 0;
	acc->component_type = json_get_int(a, "componentType");
	acc->count = json_get_int(a, "count");
	type = json_as_string(json_get(a, "type"));
	if (type)
		ft_strlcpy(acc->type, type, 16);
}

void	glb_parse_buffer_view(t_json_value *json, int index, t_buffer_view *bv)
{
	t_json_value	*views;
	t_json_value	*v;

	ft_memset(bv, 0, sizeof(t_buffer_view));
	views = json_get(json, "bufferViews");
	v = json_at(views, index);
	if (!v)
		return ;
	bv->buffer = json_get_int(v, "buffer");
	bv->byte_offset = json_get_int(v, "byteOffset");
	if (bv->byte_offset < 0)
		bv->byte_offset = 0;
	bv->byte_length = json_get_int(v, "byteLength");
	bv->byte_stride = json_get_int(v, "byteStride");
	if (bv->byte_stride < 0)
		bv->byte_stride = 0;
}
