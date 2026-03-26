/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 10:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

static bool	process_scene_config(t_scene *scene, t_parse_obj *obj, bool *h)
{
	if (obj->type == TYPE_CAMERA)
	{
		scene->camera = obj->data.camera;
		return (*h = true);
	}
	if (obj->type == TYPE_AMBIENT)
	{
		scene->ambient = obj->data.ambient;
		return (*h = true);
	}
	if (obj->type == TYPE_LIGHT)
		return (*h = true, scene_add_light(scene, obj->data.light));
	return (false);
}

static bool	process_basic_geometry(t_scene *scene, t_parse_obj *obj, bool *h)
{
	if (obj->type == TYPE_SPHERE)
		return (*h = true, scene_add_sphere(scene, obj->data.sphere));
	if (obj->type == TYPE_PLANE)
		return (*h = true, scene_add_plane(scene, obj->data.plane));
	if (obj->type == TYPE_CYLINDER)
		return (*h = true, scene_add_cylinder(scene, obj->data.cylinder));
	if (obj->type == TYPE_CONE)
		return (*h = true, scene_add_cone(scene, obj->data.cone));
	return (false);
}

static bool	process_poly_geometry(t_scene *scene, t_parse_obj *obj, bool *h)
{
	if (obj->type == TYPE_TRI)
		return (*h = true, scene_add_tri(scene, obj->data.tri_shape));
	if (obj->type == TYPE_RECT)
		return (*h = true, scene_add_rect(scene, obj->data.rect));
	if (obj->type == TYPE_PYRAMID)
		return (*h = true, scene_add_pyramid(scene, obj->data.pyramid));
	if (obj->type == TYPE_BOX)
		return (*h = true, scene_add_box(scene, obj->data.box));
	if (obj->type == TYPE_CAPSULE)
		return (*h = true, scene_add_capsule(scene, obj->data.capsule));
	return (false);
}

static bool	process_mesh_assets(t_scene *scene, t_parse_obj *obj)
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
	bool	handled;
	bool	res;

	handled = false;
	res = process_scene_config(scene, &obj, &handled);
	if (handled)
		return (res);
	res = process_basic_geometry(scene, &obj, &handled);
	if (handled)
		return (res);
	res = process_poly_geometry(scene, &obj, &handled);
	if (handled)
		return (res);
	if (obj.type == TYPE_MESH || obj.type == TYPE_ANIM)
		return (process_mesh_assets(scene, &obj));
	return (true);
}
