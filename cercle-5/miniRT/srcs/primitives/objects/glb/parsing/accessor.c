/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:10:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Parses a GLTF accessor into a local t_accessor structure, resolving
 * its buffer view, byte offset, component type, and count.
 */
void	glb_parse_accessor(t_json_value *json, int idx, t_accessor *out)
{
	t_json_value	*acc;
	t_index			val;

	acc = json_at(json_get(json, "accessors"), idx);
	if (!acc)
		return ;
	val = json_get_size_t(acc, "bufferView");
	out->buffer_view = val.i;
	val = json_get_size_t(acc, "byteOffset");
	out->byte_offset = val.i;
	val = json_get_size_t(acc, "componentType");
	out->component_type = val.i;
	val = json_get_size_t(acc, "count");
	out->count = val.i;
}
