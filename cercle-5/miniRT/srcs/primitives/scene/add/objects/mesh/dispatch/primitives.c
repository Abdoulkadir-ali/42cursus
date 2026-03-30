/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:52:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	process_primitive(t_scene *scene, t_parse_obj obj)
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
	return (false);
}
