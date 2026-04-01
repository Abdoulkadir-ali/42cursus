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
#include "scene.h"

static bool	process_rect(t_scene *sc, t_rect *r)
{
	return (scene_add_rect(sc, *r));
}

static bool	process_pyramid(t_scene *sc, t_pyramid *py)
{
	return (scene_add_pyramid(sc, *py));
}

static bool	process_polygon(t_scene *sc, t_parse_obj *obj)
{
	if (obj->type == TYPE_TRI)
		return (scene_add_tri(sc, obj->data.tri_shape));
	if (obj->type == TYPE_RECT)
		return (process_rect(sc, &obj->data.rect));
	if (obj->type == TYPE_PYRAMID)
		return (process_pyramid(sc, &obj->data.pyramid));
	return (false);
}

static bool	process_mesh_object(t_scene *scene, t_parse_obj *obj)
{
	bool		ret;

	ret = scene_add_collection(scene, obj);
	free(obj->data.mesh_info.path);
	return (ret);
}

bool	process_object(t_scene *scene, t_parse_obj obj)
{
	if (obj.type == TYPE_SPHERE || obj.type == TYPE_PLANE
		|| obj.type == TYPE_CYLINDER || obj.type == TYPE_CONE
		|| obj.type == TYPE_LIGHT)
		return (process_primitive(scene, obj));
	if (obj.type == TYPE_CAMERA || obj.type == TYPE_AMBIENT)
		return (process_system(scene, obj));
	if (obj.type == TYPE_ANIM || obj.type == TYPE_MESH)
		return (process_mesh_object(scene, &obj));
	if (obj.type == TYPE_TRI || obj.type == TYPE_RECT
		|| obj.type == TYPE_PYRAMID)
		return (process_polygon(scene, &obj));
	if (obj.type == TYPE_BOX)
		return (scene_add_box(scene, obj.data.box));
	if (obj.type == TYPE_CAPSULE)
		return (scene_add_capsule(scene, obj.data.capsule));
	return (true);
}
