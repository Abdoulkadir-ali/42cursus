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

#include "loader.h"

void	obj_free_obj(t_obj *obj)
{
	free(obj->temp_v);
	free(obj->temp_vt);
	free(obj->temp_vn);
}

void	obj_init_mesh(t_mesh_asset *mesh, t_obj *obj)
{
	ft_memset(mesh, 0, sizeof(t_mesh_asset));
	mesh->transform.scale = vec3(1, 1, 1);
	mesh->vertices = obj->out_v;
	mesh->normals = obj->out_vn;
	mesh->uvs = obj->out_vt;
	mesh->indices = obj->out_i;
	mesh->vertex_count = obj->out_v_count;
	mesh->tri_count = obj->out_i_count / 3;
}

void	obj_set_mat_id(t_mesh_asset *mesh, t_obj *obj)
{
	mesh->mat_id = 0;
	if (obj->current_mat_id >= 0)
		mesh->mat_id = obj->current_mat_id;
	else if (obj->first_mtl_id >= 0)
		mesh->mat_id = obj->first_mtl_id;
}
