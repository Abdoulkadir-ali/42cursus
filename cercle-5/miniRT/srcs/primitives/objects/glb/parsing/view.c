/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:36:35 by abdoali          ###   ########.fr       */
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
	t_index			val;

	ft_memset(out, 0, sizeof(t_buffer_view));
	bv = json_at(json_get(json, "bufferViews"), idx);
	if (!bv)
		return ;
	val = json_get_size_t(bv, "buffer");
	out->buffer = val.i;
	val = json_get_size_t(bv, "byteOffset");
	out->byte_offset = val.i;
	val = json_get_size_t(bv, "byteLength");
	out->byte_length = val.i;
	val = json_get_size_t(bv, "byteStride");
	out->byte_stride = val.i;
}
