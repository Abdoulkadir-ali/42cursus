/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:59:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static t_json_value	*get_primitive(t_json_value *json, int mesh_idx, int prim_idx)
{
	t_json_value	*meshes;
	t_json_value	*m;
	t_json_value	*primitives;

	meshes = json_get(json, "meshes");
	m = json_at(meshes, mesh_idx);
	if (m == NULL)
		return (NULL);
	primitives = json_get(m, "primitives");
	return (json_at(primitives, prim_idx));
}

static bool	get_ids(t_json_value *prim, int ids[6])
{
	t_json_value	*attr;

	if (prim == NULL)
		return (false);
	attr = json_get(prim, "attributes");
	if (attr == NULL)
		return (false);
	ids[0] = json_get_int(attr, "POSITION");
	ids[1] = json_get_int(attr, "NORMAL");
	ids[2] = json_get_int(attr, "TEXCOORD_0");
	ids[3] = json_get_int(prim, "indices");
	ids[4] = json_get_int(attr, "JOINTS_0");
	ids[5] = json_get_int(attr, "WEIGHTS_0");
	if (ids[0] < 0 || ids[3] < 0)
		return (false);
	return (true);
}

static bool	alloc_mesh(t_mesh *mesh, t_json_value *json, int ids[6])
{
	t_glb_accessor	acc;

	glb_parse_accessor(json, ids[0], &acc);
	if (acc.count == 0)
		return (false);
	mesh->vertex_count = (int)acc.count;
	mesh->vertices = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->normals = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(acc.count, sizeof(t_vec2));
	if (ids[4] >= 0 && ids[5] >= 0)
		mesh->skin_data = ft_calloc(acc.count, sizeof(t_bone_weight));
	if (mesh->vertices == NULL || mesh->normals == NULL || mesh->uvs == NULL)
		return (false);
	return (true);
}

static void	fill_indices(t_json_value *json, char *bin, t_glb_accessor *acc,
	t_mesh *mesh)
{
	t_glb_buffer_view	bv;

	glb_parse_buffer_view(json, acc->buffer_view, &bv);
	acc->type_size = sizeof(int);
	acc->stride = sizeof(int);
	glb_extract_data(bin, acc, &bv, mesh->indices);
}

bool	glb_load_primitive(t_mesh *mesh, t_json_value *json, char *bin,
		int mesh_idx, int prim_idx, int mat_id)
{
	t_json_value	*prim;
	int				ids[6];
	t_glb_accessor		idx_acc;

	prim = get_primitive(json, mesh_idx, prim_idx);
	if (get_ids(prim, ids) == false)
		return (false);
	if (alloc_mesh(mesh, json, ids) == false)
		return (false);
	glb_parse_accessor(json, ids[3], &idx_acc);
	mesh->indices = ft_calloc(idx_acc.count, sizeof(int));
	if (mesh->indices == NULL)
		return (false);
	mesh->tri_count = (int)idx_acc.count / 3;
	mesh->mat_id = mat_id;
	glb_fill_attributes(mesh, json, bin, ids);
	if (idx_acc.component_type == 5123)
		glb_handle_indices_short(mesh, json, bin, ids[3]);
	else
		fill_indices(json, bin, &idx_acc, mesh);
	glb_compute_mesh_bbox(mesh);
	return (true);
}

void	glb_compute_mesh_bbox(t_mesh *mesh)
{
	size_t	i;

	if (mesh->vertices == NULL || mesh->vertex_count == 0)
		return ;
	mesh->bbox = aabb_create_empty();
	i = 0;
	while (i < (size_t)mesh->vertex_count)
		aabb_expand_point(&mesh->bbox, mesh->vertices[i++]);
}

