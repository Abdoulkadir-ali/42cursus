/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdio.h>
#include <stdarg.h>

static void	glb_log(const char *fmt, ...)
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

static void	compute_mesh_bbox(t_mesh *mesh)
{
	int	i;

	mesh->bbox = aabb_create_empty();
	if (mesh->vertex_count == 0)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->bbox.min = vec3_min(mesh->bbox.min, mesh->vertices[i]);
		mesh->bbox.max = vec3_max(mesh->bbox.max, mesh->vertices[i]);
		i++;
	}
}

static t_json_value	*get_primitive(t_json_value *json, int mesh_idx, int prim_idx)
{
	t_json_value	*meshes;
	t_json_value	*m;
	t_json_value	*primitives;

	meshes = json_get(json, "meshes");
	m = json_at(meshes, mesh_idx);
	if (!m)
		return (NULL);
	primitives = json_get(m, "primitives");
	return (json_at(primitives, prim_idx));
}

static bool	get_attribute_ids(t_json_value *prim, int ids[6])
{
	t_json_value	*attr;

	if (!prim)
		return (false);
	attr = json_get(prim, "attributes");
	if (!attr)
		return (false);
	ids[0] = json_get_int(attr, "POSITION");
	ids[1] = json_get_int(attr, "NORMAL");
	ids[2] = json_get_int(attr, "TEXCOORD_0");
	ids[3] = json_get_int(prim, "indices");
	ids[4] = json_get_int(attr, "JOINTS_0");
	ids[5] = json_get_int(attr, "WEIGHTS_0");
	
	glb_log("GLB: Primitive Attributes found -> POS:%d, NORM:%d, UV:%d, IDX:%d, JNT:%d, WGT:%d\n",
		ids[0], ids[1], ids[2], ids[3], ids[4], ids[5]);
	
	if (ids[0] < 0 || ids[3] < 0)
		return (false);
	return (true);
}

static bool	alloc_mesh_arrays(t_mesh *mesh, t_json_value *json, int ids[6],
		t_accessor *idx_acc)
{
	t_accessor	acc;

	glb_parse_accessor(json, ids[0], &acc);
	if (acc.count == 0)
		return (false);
	mesh->vertex_count = acc.count;
	mesh->vertices = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->normals = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(acc.count, sizeof(t_vec2));
	
	/* Skinning allocation */
	if (ids[4] >= 0 && ids[5] >= 0)
	{
		mesh->skin_data = ft_calloc(acc.count, sizeof(t_bone_weight));
		if (!mesh->skin_data)
			return (false);
		glb_log("GLB: Allocated skin data for %d vertices\n", acc.count);
	}
	else
		mesh->skin_data = NULL;

	glb_parse_accessor(json, ids[3], idx_acc);
	if (idx_acc->count == 0)
		return (false);
	mesh->indices = ft_calloc(idx_acc->count, sizeof(int));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->indices)
		return (false);
	mesh->tri_count = idx_acc->count / 3;
	return (true);
}

static void	fill_indices_int(t_json_value *json, char *bin, t_accessor *acc,
		t_mesh *mesh)
{
	t_buffer_view	bv;
	t_extract_ctx	ctx;

	glb_parse_buffer_view(json, acc->buffer_view, &bv);
	ctx = (t_extract_ctx){bin, acc, &bv, mesh->indices, sizeof(int),
		acc->count, sizeof(int)};
	glb_extract_data(ctx);
}

bool	glb_load_primitive(t_mesh *mesh, t_json_value *json, char *bin,
		int mesh_idx, int prim_idx, int mat_id)
{
	t_json_value	*prim;
	int				ids[6];
	t_accessor		idx_acc;

	prim = get_primitive(json, mesh_idx, prim_idx);
	if (!get_attribute_ids(prim, ids))
		return (false);
	if (!alloc_mesh_arrays(mesh, json, ids, &idx_acc))
		return (false);
	mesh->mat_id = mat_id;
	glb_fill_attributes(mesh, json, bin, ids);
	if (idx_acc.component_type == 5123)
		glb_handle_indices_short(mesh, json, bin, ids[3]);
	else
		fill_indices_int(json, bin, &idx_acc, mesh);
	compute_mesh_bbox(mesh);
	return (true);
}
