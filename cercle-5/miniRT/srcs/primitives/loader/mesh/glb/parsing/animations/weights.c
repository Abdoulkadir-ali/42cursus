/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 19:33:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 18:12:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for filling Vec3 attributes (Position, Normal).
 */
static void	fill_v3(t_json_value *json, char *bin, t_vec3 *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	if (acc.count <= 0)
		return ;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 3 * acc.count);
	if (tmp == NULL)
		return ;
	glb_extract_data(bin, &acc, &bv, tmp);
	i = 0;
	while (i < acc.count)
	{
		dst[i] = vec3(tmp[i * 3], tmp[i * 3 + 1], tmp[i * 3 + 2]);
		i++;
	}
	free(tmp);
}

/**
 * @brief Logic for filling Joint indices (Skinning).
 */
static void	f_joints(t_json_value *j, char *b, t_bone_weight *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	unsigned short	*tmp;
	int				i;

	glb_parse_accessor(j, id, &acc);
	glb_parse_buffer_view(j, acc.buffer_view, &bv);
	tmp = malloc(sizeof(unsigned short) * 4 * acc.count);
	if (tmp == NULL)
		return ;
	acc.stride = sizeof(unsigned short) * 4;
	acc.type_size = sizeof(unsigned short) * 4;
	glb_extract_data(b, &acc, &bv, tmp);
	i = 0;
	while (i < acc.count)
	{
		dst[i].bone_ids[0] = tmp[i * 4];
		dst[i].bone_ids[1] = tmp[i * 4 + 1];
		dst[i].bone_ids[2] = tmp[i * 4 + 2];
		dst[i].bone_ids[3] = tmp[i * 4 + 3];
		i++;
	}
	free(tmp);
}

/**
 * @brief Logic for filling Bone weights (Skinning).
 */
static void	f_weights(t_json_value *j, char *b, t_bone_weight *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(j, id, &acc);
	glb_parse_buffer_view(j, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 4 * acc.count);
	if (tmp == NULL)
		return ;
	acc.stride = sizeof(float) * 4;
	acc.type_size = sizeof(float) * 4;
	glb_extract_data(b, &acc, &bv, tmp);
	i = 0;
	while (i < acc.count)
	{
		dst[i].weights[0] = tmp[i * 4];
		dst[i].weights[1] = tmp[i * 4 + 1];
		dst[i].weights[2] = tmp[i * 4 + 2];
		dst[i].weights[3] = tmp[i * 4 + 3];
		i++;
	}
	free(tmp);
}

/**
 * @brief Logic for filling Vec2 attributes (UVs).
 */
static void	fill_v2(t_json_value *json, char *bin, t_vec2 *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 2 * acc.count);
	if (tmp == NULL)
		return ;
	acc.stride = sizeof(float) * 2;
	acc.type_size = sizeof(float) * 2;
	glb_extract_data(bin, &acc, &bv, tmp);
	i = 0;
	while (i < acc.count)
	{
		dst[i] = vec2(tmp[i * 2], 1.0f - tmp[i * 2 + 1]);
		i++;
	}
	free(tmp);
}

/**
 * @brief Public dispatcher for GLB attribute filling.
 */
void	glb_fill_attributes(t_mesh *mesh, t_json_value *json, char *bin,
		int ids[6])
{
	fill_v3(json, bin, mesh->vertices, ids[0]);
	if (ids[1] != -1)
		fill_v3(json, bin, mesh->normals, ids[1]);
	if (ids[2] != -1)
		fill_v2(json, bin, mesh->uvs, ids[2]);
	if (ids[4] != -1 && ids[5] != -1 && mesh->skin_data != NULL)
	{
		f_joints(json, bin, mesh->skin_data, ids[4]);
		f_weights(json, bin, mesh->skin_data, ids[5]);
	}
}
