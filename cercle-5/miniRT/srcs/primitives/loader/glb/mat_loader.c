/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:11:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "surface.h"

static void	extract_glb_texture(t_json_value *json, char *bin,
		t_raw_material *mat, t_json_value *pbr)
{
	t_json_value	*base_color_tex;
	t_json_value	*textures;
	t_json_value	*t;
	t_json_value	*images;
	t_json_value	*img;
	t_buffer_view	bv;
	int				tex_idx;
	int				source;
	int				bv_idx;

	base_color_tex = json_get(pbr, "baseColorTexture");
	if (!base_color_tex)
		return ;
	tex_idx = json_get_int(base_color_tex, "index");
	textures = json_get(json, "textures");
	t = json_at(textures, tex_idx);
	if (!t)
		return ;
	source = json_get_int(t, "source");
	images = json_get(json, "images");
	img = json_at(images, source);
	if (!img)
		return ;
	bv_idx = json_get_int(img, "bufferView");
	if (bv_idx < 0)
		return ;
	glb_parse_buffer_view(json, bv_idx, &bv);
	mat->tex_data = (unsigned char *)(bin + bv.byte_offset);
	mat->tex_len = bv.byte_length;
	mat->has_tex = true;
}

static void	parse_glb_material_raw(t_json_value *json, char *bin,
		int mat_idx, t_raw_material *out)
{
	t_json_value	*materials;
	t_json_value	*m;
	t_json_value	*pbr;
	t_json_value	*color;
	t_vec3			albedo;

	materials = json_get(json, "materials");
	m = json_at(materials, mat_idx);
	if (!m || m->type != JSON_OBJECT)
		return ;
	albedo = get_colors()->white;
	pbr = json_get(m, "pbrMetallicRoughness");
	if (pbr)
	{
		color = json_get(pbr, "baseColorFactor");
		if (color && color->type == JSON_ARRAY && color->array.count >= 3)
		{
			albedo.x = json_as_number(json_at(color, 0)) * 255.0;
			albedo.y = json_as_number(json_at(color, 1)) * 255.0;
			albedo.z = json_as_number(json_at(color, 2)) * 255.0;
		}
		extract_glb_texture(json, bin, out, pbr);
	}
	else
	{
		/* Fallback check */
		extract_glb_texture(json, bin, out, m);
	}
	out->color = albedo;
}

t_raw_material	*glb_extract_materials(t_json_value *json, char *bin, int *out_count)
{
	t_json_value	*materials;
	int				count;
	t_raw_material	*raw_mats;
	int				i;

	materials = json_get(json, "materials");
	if (!materials || materials->type != JSON_ARRAY)
	{
		*out_count = 0;
		return (NULL);
	}
	count = (int)materials->array.count;
	*out_count = count;
	raw_mats = ft_calloc(count, sizeof(t_raw_material));
	if (!raw_mats)
		return (NULL);
	i = -1;
	while (++i < count)
		parse_glb_material_raw(json, bin, i, &raw_mats[i]);
	return (raw_mats);
}
