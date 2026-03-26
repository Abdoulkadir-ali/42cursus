/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Retrieves the physics body of the currently selected scene object.
 * @param gui Pointer to the GUI.
 * @return t_physics_body* Pointer to the physics body, or NULL.
 */
t_physics_body	*get_selected_physics(t_gui *gui)
{
	t_scene	*sc;
	int		idx;

	sc = gui->scene;
	idx = gui->selection.index;
	if (gui->selection.type == TYPE_SPHERE)
		return (&sc->spheres[idx].phys);
	if (gui->selection.type == TYPE_TRI)
		return (&sc->tris[idx].phys);
	if (gui->selection.type == TYPE_CYLINDER)
		return (&sc->cylinders[idx].phys);
	if (gui->selection.type == TYPE_RECT)
		return (&sc->rects[idx].phys);
	if (gui->selection.type == TYPE_PYRAMID)
		return (&sc->pyramids[idx].phys);
	if (gui->selection.type == TYPE_BOX)
		return (&sc->boxes[idx].phys);
	if (gui->selection.type == TYPE_CAPSULE)
		return (&sc->capsules[idx].phys);
	if (gui->selection.type == TYPE_MESH)
		return (&sc->groups[idx].phys);
	return (NULL);
}
