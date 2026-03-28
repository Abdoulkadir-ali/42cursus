/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:59:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static void	extract_pbr(t_json_value *json, char *bin, t_material *m,
		t_json_value *mat_j)
{
	t_json_value	*pbr;
	t_json_value	*color;
	t_json_value	*emis;

	(void)json;
	(void)bin;
	pbr = json_get(mat_j, "pbrMetallicRoughness");
	if (pbr)
	{
		color = json_get(pbr, "baseColorFactor");
		if (color && color->type == JSON_ARRAY && color->array.count >= 3)
		{
			m->albedo_map.color_a.x = json_as_number(json_at(color, 0)) * 255.0;
			m->albedo_map.color_a.y = json_as_number(json_at(color, 1)) * 255.0;
			m->albedo_map.color_a.z = json_as_number(json_at(color, 2)) * 255.0;
		}
		m->metallic = json_as_number(json_get(pbr, "metallicFactor"));
		m->roughness = json_as_number(json_get(pbr, "roughnessFactor"));
	}
	emis = json_get(mat_j, "emissiveFactor");
	if (emis && emis->type == JSON_ARRAY && emis->array.count >= 3)
	{
		m->emission.x = json_as_number(json_at(emis, 0));
		m->emission.y = json_as_number(json_at(emis, 1));
		m->emission.z = json_as_number(json_at(emis, 2));
	}
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
