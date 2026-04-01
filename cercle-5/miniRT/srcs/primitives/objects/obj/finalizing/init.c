/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static void	obj_fill_vertices(t_mesh *mesh, t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i < obj->out_v_count)
	{
		mesh->vertices[i].pos = obj->out_v[i];
		if (obj->out_vn)
			mesh->vertices[i].normal = obj->out_vn[i];
		if (obj->out_vt)
			mesh->vertices[i].uv = obj->out_vt[i];
		i++;
	}
}

static void	obj_fill_triangles(t_mesh *mesh, t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i < obj->out_i_count / 3)
	{
		mesh->triangles[i].v[0] = obj->out_i[i * 3];
		mesh->triangles[i].v[1] = obj->out_i[i * 3 + 1];
		mesh->triangles[i].v[2] = obj->out_i[i * 3 + 2];
		i++;
	}
}

void	obj_init_mesh(t_mesh *mesh, t_obj *obj, const char *path)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->name = ft_strdup(path);
	mesh->vertices = ft_calloc(obj->out_v_count, sizeof(t_vertex));
	if (!mesh->vertices)
		return ;
	obj_fill_vertices(mesh, obj);
	mesh->vertex_count = obj->out_v_count;
	mesh->triangles = ft_calloc(obj->out_i_count / 3, sizeof(t_triangle));
	if (!mesh->triangles)
		return ;
	obj_fill_triangles(mesh, obj);
	mesh->tri_count = obj->out_i_count / 3;
	mesh->bbox = obj->bbox;
}
