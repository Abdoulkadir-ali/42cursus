/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static void	finalize_mesh_local(t_mesh *mesh)
{
	/* Capture base vertices */
	if ((mesh->skin_data || mesh->node_idx >= 0) && mesh->vertex_count > 0)
	{
		mesh->base_vertices = malloc(sizeof(t_vec3) * mesh->vertex_count);
		mesh->base_normals = malloc(sizeof(t_vec3) * mesh->vertex_count);
		if (mesh->base_vertices && mesh->vertices)
			ft_memcpy(mesh->base_vertices, mesh->vertices,
				sizeof(t_vec3) * mesh->vertex_count);
		if (mesh->base_normals && mesh->normals)
			ft_memcpy(mesh->base_normals, mesh->normals,
				sizeof(t_vec3) * mesh->vertex_count);
	}
}

static int	count_glb_meshes(t_json_value *meshes_json)
{
	int				count;
	int				i;
	t_json_value	*m;
	t_json_value	*prims;

	count = 0;
	i = -1;
	while (++i < (int)meshes_json->array.count)
	{
		m = json_at(meshes_json, i);
		prims = json_get(m, "primitives");
		if (prims && prims->type == JSON_ARRAY)
			count += prims->array.count;
	}
	return (count);
}

static void	glb_load_skeleton_impl(t_mesh *mesh, t_json_value *json, char *bin,
		int extra_count)
{
	void glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin, int extra_count);
	glb_load_skeleton(mesh, json, bin, extra_count);
}

static void	process_glb_meshes(t_raw_model *out, t_json_value *json, char *bin,
		const char *path)
{
	t_json_value	*meshes_j;
	t_json_value	*m_j;
	t_json_value	*prims;
	t_mesh			mesh;
	int				i[5]; /* i, j, mat_idx, mesh_idx, node_count */

	meshes_j = json_get(json, "meshes");
	if (!meshes_j || meshes_j->type != JSON_ARRAY) return ;
	i[3] = count_glb_meshes(meshes_j);
	out->meshes = malloc(sizeof(t_mesh) * i[3]);
	out->mesh_mat_indices = malloc(sizeof(int) * i[3]);
	if (!out->meshes || !out->mesh_mat_indices) return ;
	i[0] = -1;
	while (++i[0] < (int)meshes_j->array.count)
	{
		m_j = json_at(meshes_j, i[0]);
		prims = json_get(m_j, "primitives");
		i[1] = -1;
		while (++i[1] < (int)prims->array.count)
		{
			i[2] = json_get_int(json_at(prims, i[1]), "material");
			init_mesh(&mesh, path);
			if (glb_load_primitive(&mesh, json, bin, i[0], i[1], i[2]))
			{
				glb_load_skeleton_impl(&mesh, json, bin, 0);
				finalize_mesh_local(&mesh);
				out->meshes[out->mesh_count] = mesh;
				out->mesh_mat_indices[out->mesh_count++] = i[2];
			}
			else mesh_free(&mesh);
		}
	}
}

bool	glb_load(const char *path, t_raw_model *out)
{
	int				fd;
	char			*buf[2];
	t_json_value	*json;

	ft_memset(out, 0, sizeof(*out));
	buf[0] = NULL;
	buf[1] = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0) return (false);
	if (!glb_read_buffers(fd, buf))
	{
		close(fd);
		return (false);
	}
	close(fd);
	json = json_parse(buf[0]);
	if (json)
	{
		process_glb_meshes(out, json, buf[1], path);
		json_free(json);
	}
	free(buf[0]);
	free(buf[1]);
	return (out->mesh_count > 0);
}
