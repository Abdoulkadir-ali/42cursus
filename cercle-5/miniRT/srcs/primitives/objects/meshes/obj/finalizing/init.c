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
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->transform.scale = vec3(1, 1, 1);
	mesh->name = ft_strdup(path);
	mesh->vertices = obj->out_v;
	mesh->normals = obj->out_vn;
	mesh->uvs = obj->out_vt;
	mesh->indices = obj->out_i;
	mesh->vertex_count = obj->out_v_count;
	mesh->tri_count = obj->out_i_count / 3;
	mesh->bbox = obj->bbox;
}

