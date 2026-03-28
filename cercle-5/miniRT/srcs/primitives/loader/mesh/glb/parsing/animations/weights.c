/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:38:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static void	fill_v3(t_json_value *json, char *bin, t_vec3 *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 3 * acc.count);
	if (!tmp) return ;
	glb_extract_data(bin, &acc, &bv, tmp);
	i = 0;
	while (i < acc.count)
	{
		dst[i] = vec3(tmp[i * 3], tmp[i * 3 + 1], tmp[i * 3 + 2]);
		i++;
	}
	free(tmp);
}

static void	fill_joints(t_json_value *j, char *b, uint16_t *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	unsigned short	*tmp;

	glb_parse_accessor(j, id, &acc);
	glb_parse_buffer_view(j, acc.buffer_view, &bv);
	tmp = malloc(sizeof(unsigned short) * 4 * acc.count);
	if (!tmp) return ;
	glb_extract_data(b, &acc, &bv, tmp);
	ft_memcpy(dst, tmp, sizeof(unsigned short) * 4 * acc.count);
	free(tmp);
}

static void	fill_weights(t_json_value *j, char *b, float *dst, int id)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	float			*tmp;

	glb_parse_accessor(j, id, &acc);
	glb_parse_buffer_view(j, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 4 * acc.count);
	if (!tmp) return ;
	glb_extract_data(b, &acc, &bv, tmp);
	ft_memcpy(dst, tmp, sizeof(float) * 4 * acc.count);
	free(tmp);
}

void	glb_fill_attributes(t_mesh *mesh, t_json_value *json, char *bin,
		int ids[6])
{
	fill_v3(json, bin, mesh->vertices, ids[0]);
	if (ids[1] != -1)
		fill_v3(json, bin, mesh->normals, ids[1]);
	
	if (ids[4] != -1 && ids[5] != -1)
	{
		mesh->bone_ids = malloc(sizeof(uint16_t) * 4 * mesh->vertex_count);
		mesh->weights = malloc(sizeof(float) * 4 * mesh->vertex_count);
		mesh->weight_counts = malloc(sizeof(int) * mesh->vertex_count);
		mesh->weight_offsets = malloc(sizeof(int) * mesh->vertex_count);
		
		fill_joints(json, bin, mesh->bone_ids, ids[4]);
		fill_weights(json, bin, mesh->weights, ids[5]);
		
		int i = 0;
		while (i < (int)mesh->vertex_count)
		{
			mesh->weight_offsets[i] = i * 4;
			mesh->weight_counts[i] = 4;
			i++;
		}
	}
}
