/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 03:10:00 by abdoali          ###   ########.fr       */
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
 * @brief Cleanup helper for partially allocated material arrays.
 */
static t_material	*cleanup_mats(t_material *mats, size_t n)
{
	size_t	i;

	if (mats == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (mats[i].name)
			free(mats[i].name);
		i++;
	}
	free(mats);
	return (NULL);
}

/**
 * @brief Extracts all materials from a GLB JSON into a typed array.
 */
t_material	*glb_extract_materials(t_json_value *json, char *bin, int *count)
{
	t_json_value	*m_j;
	t_material		*mats;
	size_t			i;

	m_j = json_get(json, "materials");
	if (!m_j || m_j->type != JSON_ARRAY)
		return (*count = 0, NULL);
	*count = (int)m_j->array.count;
	mats = ft_calloc(*count, sizeof(t_material));
	if (mats == NULL)
		return (NULL);
	i = 0;
	while (i < (size_t)*count)
	{
		mats[i].name = ft_strdup(json_as_string(json_get(json_at(m_j, i), "name")));
		if (mats[i].name == NULL)
			return (cleanup_mats(mats, i));
		mats[i].albedo_map.type = TEX_SOLID;
		extract_pbr(json, bin, &mats[i], json_at(m_j, i));
		i++;
	}
	return (mats);
}
