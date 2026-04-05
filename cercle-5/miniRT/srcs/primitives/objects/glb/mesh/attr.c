/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 16:38:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_positions(t_json_value *json, char *bin, t_mesh *m,
				int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*src;
	size_t			i;
	float			*fp;

	glb_parse_accessor(json, acc_idx, &acc);
	m->base_geometry.vertex_count = acc.count;
	m->base_geometry.vertices = ft_calloc(acc.count, sizeof(t_vec3));
	m->geometry.vertices = ft_calloc(acc.count, sizeof(t_vec3));
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	if (bv.byte_stride == 0)
		bv.byte_stride = 12;
	src = (unsigned char *)(bin + bv.byte_offset + acc.byte_offset);
	i = 0;
	while (i < acc.count)
	{
		fp = (float *)(src + i * bv.byte_stride);
		m->base_geometry.vertices[i] = vec3(fp[0], fp[1], fp[2]);
		m->geometry.vertices[i] = m->base_geometry.vertices[i];
		i++;
	}
}

static void	load_normals(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*src;
	size_t			i;
	float			*fp;

	if (acc_idx < 0)
		return ;
	glb_parse_accessor(json, acc_idx, &acc);
	m->base_normals = ft_calloc(acc.count, sizeof(t_vec3));
	m->normals = ft_calloc(acc.count, sizeof(t_vec3));
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	if (bv.byte_stride == 0)
		bv.byte_stride = 12;
	src = (unsigned char *)(bin + bv.byte_offset + acc.byte_offset);
	i = 0;
	while (i < acc.count)
	{
		fp = (float *)(src + i * bv.byte_stride);
		m->base_normals[i] = vec3(fp[0], fp[1], fp[2]);
		m->normals[i] = m->base_normals[i];
		i++;
	}
}

static void	load_uvs(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*src;
	size_t			i;
	size_t			stride;
	float			*fp;

	if (acc_idx < 0)
		return ;
	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	stride = bv.byte_stride;
	if (stride == 0)
		stride = sizeof(float) * 2;
	m->base_geometry.uvs = ft_calloc(acc.count, sizeof(t_vec2));
	src = (unsigned char *)(bin + bv.byte_offset + acc.byte_offset);
	i = 0;
	while (i < acc.count)
	{
		fp = (float *)(src + i * stride);
		m->base_geometry.uvs[i].x = fp[0];
		m->base_geometry.uvs[i].y = 1.0f - fp[1];
		i++;
	}
}

static void	load_joints(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*tmp;
	size_t			comp_sz;
	size_t			i;
	size_t			k;

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	comp_sz = 1;
	if (acc.component_type == 5123)
		comp_sz = 2;
	tmp = ft_calloc(comp_sz * 4, acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, tmp,
		comp_sz * 4, comp_sz * 4, comp_sz * 4, acc.count});
	i = 0;
	while (i < acc.count)
	{
		k = 0;
		while (k < 4)
		{
			if (acc.component_type == 5123)
				m->weights[i].bone_indices[k] = ((unsigned short *)tmp)[i * 4 + k];
			else
				m->weights[i].bone_indices[k] = ((unsigned char *)tmp)[i * 4 + k];
			k++;
		}
		i++;
	}
	free(tmp);
}

static void	load_skin_weights(t_json_value *json, char *bin, t_mesh *m,
				int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*tmp;
	size_t			comp_sz;
	size_t			i;
	size_t			k;

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	comp_sz = 4;
	if (acc.component_type == 5123)
		comp_sz = 2;
	else if (acc.component_type == 5121)
		comp_sz = 1;
	tmp = ft_calloc(comp_sz * 4, acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, tmp,
		comp_sz * 4, comp_sz * 4, comp_sz * 4, acc.count});
	i = 0;
	while (i < acc.count)
	{
		k = 0;
		while (k < 4)
		{
			if (acc.component_type == 5126)
				m->weights[i].weights[k] = ((float *)tmp)[i * 4 + k];
			else if (acc.component_type == 5123)
				m->weights[i].weights[k] = ((unsigned short *)tmp)[i * 4 + k] / 65535.0f;
			else
				m->weights[i].weights[k] = ((unsigned char *)tmp)[i * 4 + k] / 255.0f;
			k++;
		}
		i++;
	}
	free(tmp);
}

/**
 * Loads vertex attributes (positions, normals, etc.) for a GLB mesh primitive.
 */
void	glb_load_attributes(t_mesh *mesh, t_json_value *json, char *bin,
			t_json_value *attr)
{
	t_index	idx;
	t_index	idx_j;

	idx = json_get_size_t(attr, "POSITION");
	if (!idx.error)
		load_positions(json, bin, mesh, idx.i);
	idx = json_get_size_t(attr, "NORMAL");
	if (!idx.error)
		load_normals(json, bin, mesh, idx.i);
	idx = json_get_size_t(attr, "TEXCOORD_0");
	if (!idx.error)
		load_uvs(json, bin, mesh, idx.i);
	idx_j = json_get_size_t(attr, "JOINTS_0");
	idx = json_get_size_t(attr, "WEIGHTS_0");
	if (!idx_j.error && !idx.error && mesh->base_geometry.vertex_count > 0)
	{
		mesh->weights = ft_calloc(mesh->base_geometry.vertex_count, sizeof(t_bone_weight));
		if (mesh->weights)
		{
			load_joints(json, bin, mesh, idx_j.i);
			load_skin_weights(json, bin, mesh, idx.i);
		}
	}
}
