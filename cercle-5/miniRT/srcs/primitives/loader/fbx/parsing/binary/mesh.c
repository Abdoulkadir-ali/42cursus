/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Transfers and repacks vertices from fbx raw double buffers.
 */
static bool	set_v(t_fbx *f, t_mesh *m)
{
	m->vertex_count = (int)f->vc / 3;
	m->vertices = fbx_repack_vec3(f->v, m->vertex_count);
	free(f->v);
	f->v = NULL;
	if (m->vertices == NULL)
		return (false);
	return (true);
}

/**
 * @brief Transfers and repacks normals from fbx raw double buffers.
 */
static void	set_n(t_fbx *f, t_mesh *m)
{
	if (f->vn != NULL)
	{
		m->normals = fbx_repack_vec3(f->vn, (int)f->nc / 3);
		free(f->vn);
		f->vn = NULL;
	}
}

/**
 * @brief Safely releases remaining binary buffers in t_fbx.
 */
static void	rel_bin(t_fbx *f)
{
	if (f->v != NULL)
		free(f->v);
	if (f->ri != NULL)
		free(f->ri);
	if (f->vn != NULL)
		free(f->vn);
	if (f->vu != NULL)
		free(f->vu);
}

/**
 * @brief Primary mesh construction from fbx extraction arrays.
 */
bool	fbx_build_mesh(t_fbx *f)
{
	t_mesh	m;

	ft_memset(&m, 0, sizeof(t_mesh));
	if (set_v(f, &m) == false)
		return (false);
	set_n(f, &m);
	m.tri_count = (int)f->rc / 3;
	m.indices = f->ri;
	f->ri = NULL;
	m.name = ft_strdup(f->path);
	f->meshes = malloc(sizeof(t_mesh));
	if (f->meshes == NULL)
		return (false);
	f->meshes[0] = m;
	f->mesh_count = 1;
	rel_bin(f);
	return (true);
}
