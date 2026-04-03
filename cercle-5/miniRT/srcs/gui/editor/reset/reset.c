/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * Restores camera controller smooth-follow targets after a scene reset.
 */
static void	reset_cam_ctrl(t_gui *gui)
{
	t_vec3	f;

	gui->cam_ctrl.camera = &gui->scene->camera;
	gui->cam_ctrl.transform = gui->scene->camera.transform;
	f = gui->scene->camera.transform.forward;
	gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
	gui->cam_ctrl.target_rot.pitch = asin(f.y);
	gui->cam_ctrl.target_pos = gui->scene->camera.transform.pos;
	gui->cam_ctrl.target_fov = gui->scene->camera.fov;
}

/**
 * Restores per-mesh mutable fields, then frees any editor-added meshes.
 */
static void	reset_meshes(t_scene *sc, t_scene_snap *snap)
{
	size_t	i;

	i = 0;
	while (i < snap->mesh_count && i < sc->mesh_count)
	{
		sc->meshes[i].transform = snap->meshes[i].transform;
		sc->meshes[i].mat_id = snap->meshes[i].mat_id;
		sc->meshes[i].phys = snap->meshes[i].phys;
		i++;
	}
	while (i < sc->mesh_count)
		mesh_free(&sc->meshes[i++]);
	sc->mesh_count = snap->mesh_count;
	sc->mesh_group_count = snap->mesh_group_count;
}

/**
 * Restores group transforms and frees any editor-added groups.
 */
static void	reset_groups(t_scene *sc, t_scene_snap *snap)
{
	size_t	i;

	i = 0;
	while (i < snap->group_count && i < sc->group_count)
	{
		sc->groups[i].transform = snap->groups[i].transform;
		sc->groups[i].pivot = snap->groups[i].pivot;
		sc->groups[i].phys = snap->groups[i].phys;
		i++;
	}
	while (i < sc->group_count)
	{
		free(sc->groups[i].name);
		free(sc->groups[i].path);
		i++;
	}
	sc->group_count = snap->group_count;
}

static void	reset_primitives(t_scene *sc, t_scene_snap *snap)
{
	sc->sphere_count = snap->sphere_count;
	ft_memcpy(sc->spheres, snap->spheres,
		snap->sphere_count * sizeof(t_sphere));
	sc->plane_count = snap->plane_count;
	ft_memcpy(sc->planes, snap->planes,
		snap->plane_count * sizeof(t_plane));
	sc->cylinder_count = snap->cylinder_count;
	ft_memcpy(sc->cylinders, snap->cylinders,
		snap->cylinder_count * sizeof(t_cylinder));
	sc->cone_count = snap->cone_count;
	ft_memcpy(sc->cones, snap->cones, snap->cone_count * sizeof(t_cone));
	sc->light_count = snap->light_count;
	ft_memcpy(sc->lights, snap->lights,
		snap->light_count * sizeof(t_light));
	sc->mat_count = snap->mat_count;
	ft_memcpy(sc->materials, snap->materials,
		snap->mat_count * sizeof(t_material));
}

static void	reset_extra(t_scene *sc, t_scene_snap *snap)
{
	if (snap->box_count)
		ft_memcpy(sc->boxes, snap->boxes,
			snap->box_count * sizeof(t_box));
	sc->box_count = snap->box_count;
	if (snap->capsule_count)
		ft_memcpy(sc->capsules, snap->capsules,
			snap->capsule_count * sizeof(t_capsule));
	sc->capsule_count = snap->capsule_count;
	if (snap->rect_count)
		ft_memcpy(sc->rects, snap->rects,
			snap->rect_count * sizeof(t_rect));
	sc->rect_count = snap->rect_count;
	if (snap->pyramid_count)
		ft_memcpy(sc->pyramids, snap->pyramids,
			snap->pyramid_count * sizeof(t_pyramid));
	sc->pyramid_count = snap->pyramid_count;
	if (snap->tri_count)
		ft_memcpy(sc->tris, snap->tris,
			snap->tri_count * sizeof(t_tri_shape));
	sc->tri_count = snap->tri_count;
}

/**
 * Restores the scene to its post-parse state and clears editor selection.
 * Safe to call at any time during a session.
 */
void	scene_reset(t_gui *gui)
{
	t_scene_snap	*snap;
	t_scene			*sc;

	if (!gui->map_info.current)
		return ;
	snap = &gui->map_info.current->snap;
	sc = gui->scene;
	reset_primitives(sc, snap);
	reset_meshes(sc, snap);
	reset_groups(sc, snap);
	reset_extra(sc, snap);
	sc->ambient = snap->ambient;
	sc->camera = snap->camera;
	gui->ambient_color = snap->ambient_color;
	gui->ambient_intensity = snap->ambient_intensity;
	reset_cam_ctrl(gui);
	clear_selection(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
