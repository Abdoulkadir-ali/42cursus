/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 18:12:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for loading a bitmap texture from GLB into memory.
 */
static void	load_tex(t_json_value *json, char *bin, t_material *mat, int src)
{
	t_json_value	*img;
	t_glb_buffer_view	bv;
	int				bv_idx;

	img = json_at(json_get(json, "images"), src);
	if (img == NULL)
		return ;
	bv_idx = json_get_int(img, "bufferView");
	if (bv_idx < 0)
		return ;
	glb_parse_buffer_view(json, bv_idx, &bv);
	load_texture_from_memory(&mat->albedo_map, 
		(unsigned char *)(bin + bv.byte_offset), bv.byte_length);
	mat->albedo_map.type = TEX_BITMAP;
}

/**
 * @brief Parses PBR metallic roughness and populates a t_material structure.
 */
static void	extract_pbr(t_json_value *json, char *bin, t_material *out, 
			t_json_value *m)
{
	t_json_value	*pbr;
	t_json_value	*color;
	t_json_value	*tex;
	t_json_value	*t;

	pbr = json_get(m, "pbrMetallicRoughness");
	if (pbr == NULL)
		return ;
	color = json_get(pbr, "baseColorFactor");
	if (color != NULL && color->type == JSON_ARRAY && color->array.count >= 3)
	{
		out->albedo_map.color_a.x = json_as_number(json_at(color, 0)) * 255.0;
		out->albedo_map.color_a.y = json_as_number(json_at(color, 1)) * 255.0;
		out->albedo_map.color_a.z = json_as_number(json_at(color, 2)) * 255.0;
	}
	tex = json_get(pbr, "baseColorTexture");
	if (tex == NULL)
		return ;
	t = json_at(json_get(json, "textures"), json_get_int(tex, "index"));
	if (t != NULL)
		load_tex(json, bin, out, json_get_int(t, "source"));
}

/**
 * @brief Extracts all materials from a GLB JSON into a typed array.
 */
t_material	*glb_extract_materials(t_json_value *json, char *bin, int *count)
{
	t_json_value	*mats_j;
	t_material		*mats;
	size_t			i;

	mats_j = json_get(json, "materials");
	if (mats_j == NULL || mats_j->type != JSON_ARRAY)
	{
		*count = 0;
		return (NULL);
	}
	*count = (int)mats_j->array.count;
	mats = ft_calloc(*count, sizeof(t_material));
	if (mats == NULL)
		return (NULL);
	i = 0;
	while (i < (size_t)*count)
	{
		mats[i].name = ft_strdup(json_as_string(json_get(json_at(mats_j, i),
						"name")));
		mats[i].albedo_map.type = TEX_SOLID;
		extract_pbr(json, bin, &mats[i], json_at(mats_j, i));
		i++;
	}
	return (mats);
}
