/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
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

	acc = json_at(json_get(json, "accessors"), idx);
	if (!acc)
		return ;
	out->buffer_view = json_get_int(acc, "bufferView");
	out->byte_offset = json_get_int(acc, "byteOffset");
	out->component_type = json_get_int(acc, "componentType");
	out->count = (int)json_get_int(acc, "count");
	if (out->byte_offset < 0)
		out->byte_offset = 0;
}
