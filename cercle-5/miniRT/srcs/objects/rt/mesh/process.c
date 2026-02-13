/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	process_mesh_object(t_scene *scene, t_parse_obj *obj)
{
	const char	*ext;
	bool		ret;

	ext = ft_strrchr(obj->data.mesh_info.path, '.');
	ret = handle_mesh_injection(obj, ext, scene);
	free(obj->data.mesh_info.path);
	return (ret);
}

bool	process_object(t_scene *scene, t_parse_obj obj)
{
	if (obj.type == TYPE_SPHERE)
		return (scene_add_sphere(scene, obj.data.sphere));
	if (obj.type == TYPE_PLANE)
		return (scene_add_plane(scene, obj.data.plane));
	if (obj.type == TYPE_CYLINDER)
		return (scene_add_cylinder(scene, obj.data.cylinder));
	if (obj.type == TYPE_CONE)
		return (scene_add_cone(scene, obj.data.cone));
	if (obj.type == TYPE_LIGHT)
		return (scene_add_light(scene, obj.data.light));
	if (obj.type == TYPE_CAMERA)
	{
		scene->camera = obj.data.camera;
		return (true);
	}
	if (obj.type == TYPE_AMBIENT)
	{
		scene->ambient = obj.data.ambient;
		return (true);
	}
	if (obj.type == TYPE_ANIM || obj.type == TYPE_MESH)
		return (process_mesh_object(scene, &obj));
	return (true);
}
