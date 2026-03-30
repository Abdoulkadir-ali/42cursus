/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdio.h>

static void	glb_log_attr(const char *fmt, ...)
{
	va_list	args;
	FILE	*f;

	f = fopen("debug_glb.txt", "a");
	if (f)
	{
		va_start(args, fmt);
		vfprintf(f, fmt, args);
		va_end(args);
		fclose(f);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

static void	fill_attribute_vec3(t_json_value *json, char *bin, t_vec3 *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	if (acc.count <= 0)
		return ;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 3 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		sizeof(float) * 3, acc.count, sizeof(float) * 3});
	i = -1;
	while (++i < (int)acc.count)
		dst[i] = vec3(tmp[i * 3], tmp[i * 3 + 1], tmp[i * 3 + 2]);
	free(tmp);
}

static void	fill_attribute_vec2(t_json_value *json, char *bin, t_vec2 *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, id, &acc);
	if (acc.count <= 0)
		return ;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	
	/* Check if component type is actually FLOAT (5126) */
	/* If it's unsigned byte (5121) or unsigned short (5123), it needs normalization */
	if (acc.component_type != 5126)
	{
		glb_log_attr("GLB: WARNING! UVs are NOT floats (type %d). Normalization needed!\n", acc.component_type);
        // Implementing basic specific conversion for typical non-float UVs
        if (acc.component_type == 5126) { /* float, do nothing special */ }
		/* TODO: Implement conversion if we see this warning. For now, assume float but warn. */
	}

	tmp = malloc(sizeof(float) * 2 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		sizeof(float) * 2, acc.count, sizeof(float) * 2});
	
	glb_log_attr("GLB: First 5 UVs: (%.2f, %.2f), (%.2f, %.2f)...\n", 
		tmp[0], tmp[1], tmp[2], tmp[3]);

	i = -1;
	while (++i < (int)acc.count)
	{
		/* GLTF uses top-left origin, we might need to flip V depending on our texture mapper */
		/* Trying standard V flip: 1.0 - V */
		dst[i] = vec2(tmp[i * 2], 1.0f - tmp[i * 2 + 1]);
	}
	free(tmp);
}

static void fill_joints(t_json_value *json, char *bin, t_bone_weight *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*tmp;
	int				i;
	int				k;

	glb_parse_accessor(json, id, &acc);
	if (acc.count <= 0) return;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	int comp_sz = (acc.component_type == 5123) ? 2 : 1;
	
	tmp = malloc(comp_sz * 4 * acc.count);
	if (!tmp) return;
	
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		comp_sz * 4, acc.count, comp_sz * 4});

	i = -1;
	while (++i < (int)acc.count)
	{
		k = -1;
		while (++k < 4)
		{
			if (acc.component_type == 5123)
				dst[i].bone_ids[k] = ((unsigned short*)tmp)[i * 4 + k];
			else
				dst[i].bone_ids[k] = ((unsigned char*)tmp)[i * 4 + k];
		}
	}
	free(tmp);
}

static void fill_weights(t_json_value *json, char *bin, t_bone_weight *dst, int id)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*tmp;
	int				i;
	int				k;

	glb_parse_accessor(json, id, &acc);
	if (acc.count <= 0) return;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	
	int comp_sz = 1; /* Default Byte */
	if (acc.component_type == 5126) comp_sz = 4;
	else if (acc.component_type == 5123) comp_sz = 2;
	
	tmp = malloc(comp_sz * 4 * acc.count);
	if (!tmp) return;
	
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		comp_sz * 4, acc.count, comp_sz * 4});
	
	i = -1;
	while (++i < (int)acc.count)
	{
		k = -1;
		while (++k < 4)
		{
			if (acc.component_type == 5126)
				dst[i].weights[k] = ((float*)tmp)[i * 4 + k];
			else if (acc.component_type == 5123)
				dst[i].weights[k] = ((unsigned short*)tmp)[i * 4 + k] / 65535.0;
			else
				dst[i].weights[k] = ((unsigned char*)tmp)[i * 4 + k] / 255.0;
		}
	}
	free(tmp);
}

void	glb_fill_attributes(t_mesh *mesh, t_json_value *json, char *bin, int ids[6])
{
	fill_attribute_vec3(json, bin, mesh->vertices, ids[0]);
	if (ids[1] != -1)
		fill_attribute_vec3(json, bin, mesh->normals, ids[1]);
	if (ids[2] != -1)
		fill_attribute_vec2(json, bin, mesh->uvs, ids[2]);
	if (ids[4] != -1 && ids[5] != -1 && mesh->skin_data)
	{
		fill_joints(json, bin, mesh->skin_data, ids[4]);
		fill_weights(json, bin, mesh->skin_data, ids[5]);
		glb_log_attr("GLB: Skin data filled for %d vertices\n", mesh->vertex_count);
	}
}
