/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Parses a GLTF buffer view from JSON, resolving its buffer index,
 * byte offset, and total length.
 */
void	glb_parse_buffer_view(t_json_value *json, int idx, t_buffer_view *out)
{
	t_json_value	*bv;

	bv = json_at(json_get(json, "bufferViews"), idx);
	if (!bv)
		return ;
	out->buffer = json_get_int(bv, "buffer");
	out->byte_offset = json_get_int(bv, "byteOffset");
	out->byte_length = json_get_int(bv, "byteLength");
	if (out->byte_offset < 0)
		out->byte_offset = 0;
}
