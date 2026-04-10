/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 01:09:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static bool	build_vertices(t_mesh *m)
{
	size_t	i;
	size_t	n;

	n = m->base_geometry.vertex_count;
	m->vertices = ft_calloc(n, sizeof(t_vertex));
	if (!m->vertices)
		return (false);
	m->vertex_count = n;
	i = 0;
	while (i < n)
	{
		m->vertices[i].pos = m->base_geometry.vertices[i];
		if (m->base_normals)
			m->vertices[i].normal = m->base_normals[i];
		if (m->uvs)
			m->vertices[i].uv = m->uvs[i];
		i++;
	}
	return (true);
}

static void	apply_node_transform(t_mesh *m)
{
	size_t	i;
	double	tmp;

	i = 0;
	while (i < m->vertex_count)
	{
		m->vertices[i].pos = mat4_mul_pos(m->node_transform,
				m->base_geometry.vertices[i]);
		if (m->base_normals)
			m->vertices[i].normal = mat4_mul_dir(m->node_transform,
					m->base_normals[i]);
		tmp = m->vertices[i].pos.y;
		m->vertices[i].pos.y = m->vertices[i].pos.z;
		m->vertices[i].pos.z = tmp;
		tmp = m->vertices[i].normal.y;
		m->vertices[i].normal.y = m->vertices[i].normal.z;
		m->vertices[i].normal.z = tmp;
		i++;
	}
}

static void	sync_flat_normals(t_mesh *m)
{
	size_t	i;

	if (m->vertices && m->vertex_count > 0)
	{
		m->normals = malloc(sizeof(t_vec3) * m->vertex_count);
		if (m->normals)
		{
			i = 0;
			while (i < m->vertex_count)
			{
				m->normals[i] = m->vertices[i].normal;
				i++;
			}
		}
	}
}

static bool	build_triangles(t_mesh *m)
{
	size_t	count;

	count = m->base_geometry.index_count;
	m->indices = malloc(sizeof(*m->indices) * count);
	if (!m->indices)
		return (false);
	ft_memcpy(m->indices, m->base_geometry.indices,
		sizeof(*m->indices) * count);
	m->tri_count = count / 3;
	return (true);
}

void	glb_finalize_mesh(t_mesh *m)
{
	m->uvs = m->base_geometry.uvs;
	if (!m->base_geometry.vertices || m->base_geometry.vertex_count == 0)
		return ;
	if (!build_vertices(m))
		return ;
	apply_node_transform(m);
	if (m->base_geometry.indices && m->base_geometry.index_count >= 3)
	{
		if (!build_triangles(m))
			return ;
	}
	sync_flat_normals(m);
	ft_memset(&m->transform, 0, sizeof(t_transform));
	m->transform.scale = vec3(1, 1, 1);
	mesh_build_bvh(m);
}
