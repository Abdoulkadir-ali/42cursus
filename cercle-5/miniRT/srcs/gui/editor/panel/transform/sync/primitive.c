/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:56:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Synchronizes all transform components (pos/rot/scale) to SoA primitives.
 * Extracts basis vectors from rotation to update primary axis (ax-az) 
 * and tangent (tx-tz) for correctly oriented primitives like cylinders/rects.
 */
void	primitive_transform_sync(t_gui *gui)
{
	t_primitive_array	*p;
	t_transform			*tr;
	t_mat4				m;
	int					idx;

	if (!gui->selection->active || gui->selection->type == TYPE_MESH)
		return ;
	tr = get_selected_transform(gui);
	if (!tr)
		return ;
	p = &gui->scene->primitives;
	idx = gui->selection->index;
	/* Update Position */
	p->px[idx] = (float)tr->pos.x;
	p->py[idx] = (float)tr->pos.y;
	p->pz[idx] = (float)tr->pos.z;
	/* Compute Basis from Rotation for DOD Cylinders/Cones/Rects */
	m = mat4_rotation(tr->rotation);
	p->ax[idx] = (float)m.m[2][0]; p->ay[idx] = (float)m.m[2][1]; p->az[idx] = (float)m.m[2][2];
	p->tx[idx] = (float)m.m[0][0]; p->ty[idx] = (float)m.m[0][1]; p->tz[idx] = (float)m.m[0][2];
	/* Delegate specialized sync (radii/extents) to existing handlers */
	if (gui->selection->type == TYPE_SPHERE)
		sphere_scale_sync(gui);
	else if (gui->selection->type == TYPE_BOX)
		box_scale_sync(gui);
	else
		rebuild_bvh(gui);
}
