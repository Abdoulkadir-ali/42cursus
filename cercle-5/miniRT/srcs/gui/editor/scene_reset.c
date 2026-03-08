/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 00:23:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"
#include <math.h>

/*
** Copies the editable state of each primitive object array from scene into
** snap.  Sphere/plane/cylinder/cone/light are fully POD so a flat memcpy is
** safe.  Materials carry texture image pointers that are shared — we copy
** the struct value only (the GPU-side data is never freed during a session).
** Mesh geometry is never edited, so we only snapshot transform, mat_id and
** physics body per mesh.
*/
static void	snap_array(void **dst, void *src, int count, size_t sz)
{
	*dst = NULL;
	if (count <= 0)
		return ;
	*dst = malloc(count * sz);
	if (*dst)
		ft_memcpy(*dst, src, (size_t)count * sz);
}

static void	snap_meshes(t_scene_snap *snap, t_scene *sc)
{
	int	i;

	snap->mesh_count = sc->mesh_count;
	snap->meshes = NULL;
	if (sc->mesh_count <= 0)
		return ;
	snap->meshes = malloc(sc->mesh_count * sizeof(t_mesh_snap));
	if (!snap->meshes)
		return ;
	i = 0;
	while (i < sc->mesh_count)
	{
		snap->meshes[i].transform = sc->meshes[i].transform;
		snap->meshes[i].mat_id = sc->meshes[i].mat_id;
		snap->meshes[i].phys = sc->meshes[i].phys;
		i++;
	}
}

/*
** Takes a snapshot of the scene immediately after parsing.
** Called once from gui_init, before the first frame is rendered.
*/
void	scene_snap_take(t_scene_snap *snap, t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	ft_memset(snap, 0, sizeof(*snap));
	snap_array((void **)&snap->spheres, sc->spheres,
		sc->sphere_count, sizeof(t_sphere));
	snap->sphere_count = sc->sphere_count;
	snap_array((void **)&snap->planes, sc->planes,
		sc->plane_count, sizeof(t_plane));
	snap->plane_count = sc->plane_count;
	snap_array((void **)&snap->cylinders, sc->cylinders,
		sc->cylinder_count, sizeof(t_cylinder));
	snap->cylinder_count = sc->cylinder_count;
	snap_array((void **)&snap->cones, sc->cones,
		sc->cone_count, sizeof(t_cone));
	snap->cone_count = sc->cone_count;
	snap_array((void **)&snap->lights, sc->lights,
		sc->light_count, sizeof(t_light));
	snap->light_count = sc->light_count;
	snap_array((void **)&snap->materials, sc->materials,
		sc->mat_count, sizeof(t_material));
	snap->mat_count = sc->mat_count;
	snap_meshes(snap, sc);
	snap->mesh_group_count = sc->mesh_group_count;
	snap->ambient = sc->ambient;
	snap->camera = sc->camera;
	snap->ambient_color = gui->ambient_color;
	snap->ambient_intensity = gui->ambient_intensity;
}

/*
** Frees heap buffers owned by the snapshot.
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
	ft_memset(snap, 0, sizeof(*snap));
}

/*
** Restores the camera controller smooth-follow targets after scene reset.
** Mirrors the logic in init_camera().
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

/*
** Restores scene to its post-parse state and clears editor selection.
** Safe to call at any time during the session.
*/
void	scene_reset(t_gui *gui)
{
	t_scene_snap	*snap;
	t_scene			*sc;
	int				i;

	if (!gui->map_info.current)
		return ;
	snap = &gui->map_info.current->snap;
	sc = gui->scene;
	sc->sphere_count = snap->sphere_count;
	ft_memcpy(sc->spheres, snap->spheres,
		(size_t)snap->sphere_count * sizeof(t_sphere));
	sc->plane_count = snap->plane_count;
	ft_memcpy(sc->planes, snap->planes,
		(size_t)snap->plane_count * sizeof(t_plane));
	sc->cylinder_count = snap->cylinder_count;
	ft_memcpy(sc->cylinders, snap->cylinders,
		(size_t)snap->cylinder_count * sizeof(t_cylinder));
	sc->cone_count = snap->cone_count;
	ft_memcpy(sc->cones, snap->cones,
		(size_t)snap->cone_count * sizeof(t_cone));
	sc->light_count = snap->light_count;
	ft_memcpy(sc->lights, snap->lights,
		(size_t)snap->light_count * sizeof(t_light));
	sc->mat_count = snap->mat_count;
	ft_memcpy(sc->materials, snap->materials,
		(size_t)snap->mat_count * sizeof(t_material));
	i = 0;
	while (i < snap->mesh_count && i < sc->mesh_count)
	{
		sc->meshes[i].transform = snap->meshes[i].transform;
		sc->meshes[i].mat_id = snap->meshes[i].mat_id;
		sc->meshes[i].phys = snap->meshes[i].phys;
		i++;
	}
	/* Free any meshes the user added via the editor popup */
	while (i < sc->mesh_count)
	{
		mesh_free(&sc->meshes[i]);
		i++;
	}
	sc->mesh_count = snap->mesh_count;
	sc->mesh_group_count = snap->mesh_group_count;
	sc->ambient = snap->ambient;
	sc->camera = snap->camera;
	gui->ambient_color = snap->ambient_color;
	gui->ambient_intensity = snap->ambient_intensity;
	reset_cam_ctrl(gui);
	clear_selection(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
