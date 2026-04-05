/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 16:49:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "glb.h"
#include "mesh.h"

/*
** Advance all skeletal animations by `delta` seconds, rebuild the BVH for
** every mesh whose skeleton was updated, then flag a scene BVH rebuild so
** the raytracer sees the new positions on this very frame.
**
** Called exclusively from the render thread — no concurrent readers.
*/
void	anim_step(t_gui *gui, double delta)
{
	t_scene	*sc;
	t_mesh	*m;
	size_t	i;

	sc = gui->scene;
	if (!sc || !sc->clip_count)
		return ;
	if (!update_animation_engine(sc, &gui->anim_engine, delta))
		return ;
	i = 0;
	while (i < sc->mesh_count)
	{
		m = &sc->meshes[i];
		if (m->bvh_dirty)
		{
			glb_update_mesh_anim(m, sc, 0.0);
			mesh_build_bvh(m);
			if (m->bvh_node_count > 0)
				m->bbox = m->bvh_nodes[0].bbox;
			m->bvh_dirty = false;
		}
		i++;
	}
	gui->render.bvh_needs_rebuild = 1;
}
