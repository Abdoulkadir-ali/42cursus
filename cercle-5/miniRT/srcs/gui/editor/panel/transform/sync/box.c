/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 22:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Synchronizes box extents directly to the SoA storage.
 * @param gui Pointer to the GUI context.
 * 
 * Replaces legacy AoS sync with direct SoA injection.
 * Half-extents are mapped from AoS tr->scale to SoA ex/ey/ez.
 */
void	box_scale_sync(t_gui *gui)
{
	t_primitive_array	*p;
	t_transform			*tr;
	int					idx;

	if (!gui->selection->active || gui->selection->type != TYPE_BOX)
		return ;
	tr = get_selected_transform(gui);
	if (!tr)
		return ;
	p = &gui->scene->primitives;
	idx = gui->selection->index;
	/* Sync SoA extents from the transform updated by the UI sliders */
	p->ex[idx] = (float)tr->scale.x;
	p->ey[idx] = (float)tr->scale.y;
	p->ez[idx] = (float)tr->scale.z;
	/* Invalidate Scene to force BVH update and re-render */
	scene_invalidate(gui->scene);
}
