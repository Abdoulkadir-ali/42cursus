/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:31:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_from_image(t_json_value *json, char *bin, t_material *mat,
				int source)
{
	t_json_value	*img;
	t_buffer_view	bv;
	int				bv_idx;

	img = json_at(json_get(json, "images"), source);
	if (!img)
		return ;
	bv_idx = json_get_size_t(img, "bufferView", NULL);
	if (bv_idx < 0)
		return ;
	glb_parse_buffer_view(json, bv_idx, &bv);
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
	int				tex_idx;

	base_color_tex = json_get(pbr, "baseColorTexture");
	if (!base_color_tex)
		return ;
	tex_idx = json_get_size_t(base_color_tex, "index", NULL);
	t = json_at(json_get(json, "textures"), tex_idx);
	if (!t)
		return ;
	load_from_image(json, bin, mat, json_get_size_t(t, "source", NULL));
}
