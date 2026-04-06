/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:55:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

const char	*type_name_str(t_type type)
{
	if (type == TYPE_SPHERE)
		return ("Sphere");
	if (type == TYPE_PLANE)
		return ("Plane");
	if (type == TYPE_CYLINDER)
		return ("Cylinder");
	if (type == TYPE_CONE)
		return ("Cone");
	if (type == TYPE_LIGHT)
		return ("Light");
	if (type == TYPE_MESH)
		return ("Mesh");
	if (type == TYPE_TRI)
		return ("Triangle");
	if (type == TYPE_RECT)
		return ("Rectangle");
	if (type == TYPE_PYRAMID)
		return ("Pyramid");
	if (type == TYPE_BOX)
		return ("Box");
	if (type == TYPE_CAPSULE)
		return ("Capsule");
	return ("Object");
}

t_physics_body	*get_selected_physics(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE)
		return (&sc->spheres[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_TRI)
		return (&sc->tris[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_CYLINDER)
		return (&sc->cylinders[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_RECT)
		return (&sc->rects[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_PYRAMID)
		return (&sc->pyramids[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_BOX)
		return (&sc->boxes[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_CAPSULE)
		return (&sc->capsules[gui->selection.index.i].phys);
	if (gui->selection.type == TYPE_MESH)
		return (&sc->groups[gui->selection.index.i].phys);
	return (NULL);
}
