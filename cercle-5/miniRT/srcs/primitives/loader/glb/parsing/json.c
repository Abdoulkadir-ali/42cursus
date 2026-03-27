/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 18:12:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses a GLB accessor and pre-computes type dimensions.
 */
void	glb_parse_accessor(t_json_value *json, int index, t_glb_accessor *acc)
{
	t_json_value	*a;
	const char		*type;

	ft_memset(acc, 0, sizeof(t_glb_accessor));
	a = json_at(json_get(json, "accessors"), index);
	if (a == NULL)
		return ;
	acc->buffer_view = json_get_int(a, "bufferView");
	acc->byte_offset = json_get_int(a, "byteOffset");
	acc->component_type = json_get_int(a, "componentType");
	acc->count = json_get_int(a, "count");
	type = json_as_string(json_get(a, "type"));
	if (type != NULL)
		ft_strlcpy(acc->type, type, 16);
	/* Default size/stride for float VEC3 */
	acc->type_size = sizeof(float) * 3;
	acc->stride = sizeof(float) * 3;
	if (type != NULL && ft_strcmp(type, "VEC2") == 0)
	{
		acc->type_size = sizeof(float) * 2;
		acc->stride = sizeof(float) * 2;
	}
}

/**
 * @brief Parses a GLB buffer view.
 */
void	glb_parse_buffer_view(t_json_value *json, int index, t_glb_buffer_view *bv)
{
	t_json_value	*v;

	ft_memset(bv, 0, sizeof(t_glb_buffer_view));
	v = json_at(json_get(json, "bufferViews"), index);
	if (v == NULL)
		return ;
	bv->buffer = json_get_int(v, "buffer");
	bv->byte_offset = json_get_int(v, "byteOffset");
	if (bv->byte_offset < 0)
		bv->byte_offset = 0;
	bv->byte_length = json_get_int(v, "byteLength");
	bv->byte_stride = json_get_int(v, "byteStride");
}
