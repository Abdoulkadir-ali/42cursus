/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:31:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:21:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_from_image(t_json_value *json, char *bin, t_material *mat,
				t_index source)
{
	t_json_value	*img;
	t_buffer_view	bv;
	t_index			idx;

	if (source.error)
		return ;
	img = json_at(json_get(json, "images"), source.i);
	if (!img)
		return ;
	idx = json_get_size_t(img, "bufferView");
	if (idx.error)
		return ;
	glb_parse_buffer_view(json, idx.i, &bv);
	if (load_texture_from_memory(&mat->albedo_map,
			(unsigned char *)(bin + bv.byte_offset), bv.byte_length))
		glb_log("GLB: Material texture loaded successfully\n");
}

/**
 * Loads the base albedo texture for a GLB material from its PBR definition.
 */
void	load_glb_base_texture(t_json_value *json, char *bin,
			t_material *mat, t_json_value *pbr)
{
	t_json_value	*base_color_tex;
	t_json_value	*t;
	t_index			tex_idx;

	base_color_tex = json_get(pbr, "baseColorTexture");
	if (!base_color_tex)
		return ;
	tex_idx = json_get_size_t(base_color_tex, "index");
	if (tex_idx.error)
		return ;
	t = json_at(json_get(json, "textures"), tex_idx.i);
	if (!t)
		return ;
	load_from_image(json, bin, mat, json_get_size_t(t, "source"));
}
