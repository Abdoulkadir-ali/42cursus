/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static void	obj_free(t_obj *obj)
{
	free(obj->temp_v);
	free(obj->temp_vt);
	free(obj->temp_vn);
}

static void	obj_set_mat_id(t_mesh *mesh, t_obj *obj)
{
	mesh->mat_id = 0;
	if (obj->current_mat_id != (size_t)-1)
		mesh->mat_id = obj->current_mat_id;
	else if (obj->first_mtl_id != (size_t)-1)
		mesh->mat_id = obj->first_mtl_id;
}

bool	obj_build_mesh(t_scene *scene, t_obj *obj, const char *path)
{
	t_mesh	mesh;

	if (obj->out_v_count == 0)
	{
		obj_free(obj);
		return (false);
	}
	obj_generate_normals(obj);
	obj_init_mesh(&mesh, obj, path);
	obj_set_mat_id(&mesh, obj);
	obj_free(obj);
	mesh_build_bvh(&mesh);
	return (scene_add_mesh(scene, mesh));
}
