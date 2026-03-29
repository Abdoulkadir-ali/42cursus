/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:56:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Synchronizes capsule radius and height directly to the SoA storage.
 * @param gui Pointer to the GUI context.
 * 
 * Radius and height are mapped from AoS tr->scale x/y to SoA radii/heights.
 */
void	capsule_dims_sync(t_gui *gui)
{
	t_primitive_array	*p;
	t_transform			*tr;
	int					idx;

	if (!gui->selection->active || gui->selection->type != TYPE_CAPSULE)
		return ;
	tr = get_selected_transform(gui);
	if (!tr)
		return ;
	p = &gui->scene->primitives;
	idx = gui->selection->index;
	/* Radius is mapped to X scale, Height is mapped to Y scale */
	p->radii[idx] = (float)tr->scale.x;
	p->heights[idx] = (float)tr->scale.y;
	/* Update scene version to force render/sync */
	rebuild_bvh(gui);;
}
