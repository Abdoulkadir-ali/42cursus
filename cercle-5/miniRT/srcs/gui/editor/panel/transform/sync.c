/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	sync_primitive(t_gui *gui, t_scene *sc, size_t idx)
{
	if (gui->selection.type == TYPE_SPHERE)
	{
		sphere_scale_sync(gui);
		sc->spheres[idx].transform.pos = gui->transform.pos;
		sc->spheres[idx].phys.pos = gui->transform.pos;
		sc->spheres[idx].transform.scale = gui->transform.scale;
	}
	else if (gui->selection.type == TYPE_PLANE)
	{
		sc->planes[idx].transform.pos = gui->transform.pos;
		sc->planes[idx].transform.rotation = gui->transform.rotation;
		sc->planes[idx].transform.forward = vec3_norm(
				mat4_mul_vec3(mat4_rotation(gui->transform.rotation),
					vec3(0, 0, -1)));
		sc->planes[idx].transform.up = sc->planes[idx].transform.forward;
	}
}

void	transform_selection_sync(t_gui *gui)
{
	t_scene	*sc;
	size_t	idx;

	sc = gui->scene;
	idx = gui->selection.index.i;
	if (gui->selection.type == TYPE_SPHERE || gui->selection.type == TYPE_PLANE)
		sync_primitive(gui, sc, idx);
	else if (gui->selection.type == TYPE_MESH)
		mesh_transform_sync(gui);
	else if (gui->selection.type == TYPE_LIGHT && idx < sc->light_count)
		sc->lights[idx].transform.pos = gui->transform.pos;
	gui->render.bvh_needs_rebuild = 1;
}

static t_transform	*get_sel_transform(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE)
		return (&sc->spheres[gui->selection.index.i].transform);
	if (gui->selection.type == TYPE_PLANE)
		return (&sc->planes[gui->selection.index.i].transform);
	if (gui->selection.type == TYPE_CYLINDER)
		return (&sc->cylinders[gui->selection.index.i].transform);
	if (gui->selection.type == TYPE_MESH)
		return (&sc->groups[gui->selection.index.i].transform);
	if (gui->selection.type == TYPE_LIGHT)
		return (&sc->lights[gui->selection.index.i].transform);
	return (NULL);
}

void	transform_panel_sync(t_gui *gui)
{
	t_transform	*src;
	double		r;

	src = get_sel_transform(gui);
	if (!src)
		return ;
	gui->transform.pos = src->pos;
	gui->transform.rotation = src->rotation;
	gui->transform.scale = src->scale;
	if (gui->selection.type == TYPE_SPHERE
		&& gui->selection.index.i < gui->scene->sphere_count)
	{
		r = sqrt(gui->scene->spheres[gui->selection.index.i].radius_sq);
		gui->transform.scale = vec3(r, r, r);
	}
	else if (gui->selection.type == TYPE_CYLINDER
		&& gui->selection.index.i < gui->scene->cylinder_count)
	{
		r = sqrt(gui->scene->cylinders[gui->selection.index.i].radius_sq);
		gui->transform.scale = vec3(r, r, gui->transform.scale.z);
	}
}
