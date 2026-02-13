/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	get_json_ptrs(char *json, char *p[3])
{
	p[0] = json_find_key(json, "meshes");
	if (!p[0])
		return (false);
	p[1] = json_find_key(p[0], "primitives");
	if (!p[1])
		return (false);
	p[2] = json_find_key(p[1], "attributes");
	if (!p[2])
		return (false);
	return (true);
}

static bool	get_attribute_ids(char *p[3], int ids[4])
{
	ids[0] = json_get_int(p[2], "POSITION");
	ids[1] = json_get_int(p[2], "NORMAL");
	ids[2] = json_get_int(p[2], "TEXCOORD_0");
	ids[3] = json_get_int(p[1], "indices");
	if (ids[0] == -1 || ids[3] == -1)
		return (false);
	return (true);
}

static bool	alloc_mesh_arrays(t_mesh *mesh, char *json, int ids[4],
		t_accessor *idx_acc)
{
	t_accessor	acc;

	glb_parse_accessor(json, ids[0], &acc);
	mesh->vertices = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->normals = ft_calloc(acc.count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(acc.count, sizeof(t_vec2));
	glb_parse_accessor(json, ids[3], idx_acc);
	mesh->indices = ft_calloc(idx_acc->count, sizeof(int));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->indices)
		return (false);
	mesh->tri_count = idx_acc->count / 3;
	return (true);
}

static void	fill_indices_int(char *json, char *bin, t_accessor *acc,
		t_mesh *mesh)
{
	t_buffer_view	bv;
	t_extract_ctx	ctx;

	glb_parse_buffer_view(json, acc->buffer_view, &bv);
	ctx = (t_extract_ctx){bin, acc, &bv, mesh->indices, sizeof(int),
		acc->count, sizeof(int)};
	glb_extract_data(ctx);
}

bool	glb_load_mesh_data(t_mesh *mesh, char *json, char *bin)
{
	char		*p[3];
	int			ids[4];
	t_accessor	idx_acc;

	if (!get_json_ptrs(json, p))
		return (false);
	if (!get_attribute_ids(p, ids))
		return (false);
	if (!alloc_mesh_arrays(mesh, json, ids, &idx_acc))
		return (false);
	glb_fill_attributes(mesh, json, bin, ids);
	if (idx_acc.component_type == 5123)
		glb_handle_indices_short(mesh, json, bin, ids[3]);
	else
		fill_indices_int(json, bin, &idx_acc, mesh);
	return (true);
}
