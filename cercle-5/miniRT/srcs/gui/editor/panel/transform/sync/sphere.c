/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 22:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Synchronizes sphere uniform scale directly to the SoA storage.
 * @param gui Pointer to the GUI context.
 * 
 * Replaces legacy AoS sync with direct SoA injection.
 * The radius in SoA is updated from the AoS transform.scale.x.
 */
void	sphere_scale_sync(t_gui *gui)
{
	t_primitive_array	*p;
	t_transform			*tr;
	int					idx;

	if (!gui->selection->active || gui->selection->type != TYPE_SPHERE)
		return ;
	tr = get_selected_transform(gui);
	if (!tr)
		return ;
	p = &gui->scene->primitives;
	idx = gui->selection->index;
	/* In unified DOD, radii is stored in single precision float array */
	p->radii[idx] = (float)tr->scale.x;
	/* Invalidate Scene to force BVH refit/rebuild */
	scene_invalidate(gui->scene);
}
