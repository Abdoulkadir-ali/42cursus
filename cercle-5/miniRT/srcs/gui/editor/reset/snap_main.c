/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:01:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	scene_snap_take(t_scene_snap *snap, t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	ft_memset(snap, 0, sizeof(*snap));
	snap_primitives(snap, sc);
	snap_meshes(snap, sc);
	snap_groups(snap, sc);
	snap->mesh_group_count = sc->mesh_group_count;
	snap_extra(snap, sc);
	snap->ambient = sc->ambient;
	snap->camera = sc->camera;
	snap->ambient_color = gui->ambient_color;
	snap->ambient_intensity = gui->ambient_intensity;
}

void	scene_snap_free(t_scene_snap *snap)
{
	if (!snap)
		return ;
	free(snap->spheres);
	free(snap->planes);
	free(snap->cylinders);
	free(snap->cones);
	free(snap->lights);
	free(snap->materials);
	free(snap->meshes);
	free(snap->groups);
	free(snap->boxes);
	free(snap->capsules);
	free(snap->rects);
	free(snap->pyramids);
	free(snap->tris);
	ft_memset(snap, 0, sizeof(*snap));
}
