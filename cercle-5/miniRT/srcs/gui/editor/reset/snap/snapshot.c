/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Captures a full snapshot of the current scene state.
 * @param snap Pointer to the snapshot structure.
 * @param gui Pointer to the GUI context.
 */
void	scene_snapshot(t_scene_snap *snap, t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	ft_memset(snap, 0, sizeof(*snap));
	snap_sphere(snap, sc);
	snap_plane(snap, sc);
	snap_cylinder(snap, sc);
	snap_cone(snap, sc);
	snap_light(snap, sc);
	snap_box(snap, sc);
	snap_capsule(snap, sc);
	snap_rect(snap, sc);
	snap_pyramid(snap, sc);
	snap_tri(snap, sc);
	snap_mesh(snap, sc);
	snap_material(snap, sc);
	snap->ambient = sc->ambient;
	snap->camera = sc->camera;
	snap->ambient_color = gui->ambient_color;
	snap->ambient_intensity = gui->ambient_intensity;
}

/**
 * @brief Frees all buffers owned by the snapshot.
 */
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
