/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void	obj_init_mesh(t_mesh *mesh, t_obj *obj, const char *path)
{
	size_t	i;

	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->name = ft_strdup(path);
	mesh->vertices = ft_calloc(obj->out_v_count, sizeof(t_vertex));
	if (!mesh->vertices)
		return ;
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
	mesh->vertex_count = obj->out_v_count;
	mesh->triangles = ft_calloc(obj->out_i_count / 3, sizeof(t_triangle));
	if (!mesh->triangles)
		return ;
	i = 0;
	while (i < obj->out_i_count / 3)
	{
		mesh->triangles[i].v[0] = obj->out_i[i * 3];
		mesh->triangles[i].v[1] = obj->out_i[i * 3 + 1];
		mesh->triangles[i].v[2] = obj->out_i[i * 3 + 2];
		i++;
	}
	mesh->tri_count = obj->out_i_count / 3;
	mesh->bbox = obj->bbox;
}

