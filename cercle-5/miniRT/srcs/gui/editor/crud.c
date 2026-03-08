/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 01:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"
#include "objects.h"
#include "surface.h"

static t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl)
{
	t_transform	tr;

	ft_memset(&tr, 0, sizeof(tr));
	tr.pos = pos;
	tr.forward = fwd;
	tr.scale = scl;
	return (tr);
}

static t_vec3	cam_fwd_pos(t_gui *gui, double dist)
{
	return (vec3_add(gui->cam_ctrl.transform.pos,
			vec3_scale(gui->cam_ctrl.transform.forward, dist)));
}

void	editor_add_sphere(t_gui *gui)
{
	t_sphere	sp;

	if (!gui->scene)
		return ;
	ft_memset(&sp, 0, sizeof(sp));
	sp.transform = make_obj_transform(cam_fwd_pos(gui, 3.0),
			vec3(0, 0, -1), vec3(1, 1, 1));
	sp.temp_color = vec3(0.7, 0.7, 0.9);
	sp.radius_sq = 1.0;
	scene_add_sphere(gui->scene, sp);
	select_object(gui, TYPE_SPHERE, gui->scene->sphere_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_plane(t_gui *gui)
{
	t_plane	pl;

	if (!gui->scene)
		return ;
	ft_memset(&pl, 0, sizeof(pl));
	pl.transform = make_obj_transform(cam_fwd_pos(gui, 3.0),
			vec3(0, 1, 0), vec3(1, 1, 1));
	pl.temp_color = vec3(0.5, 0.5, 0.55);
	scene_add_plane(gui->scene, pl);
	select_object(gui, TYPE_PLANE, gui->scene->plane_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_cylinder(t_gui *gui)
{
	t_cylinder	cy;

	if (!gui->scene)
		return ;
	ft_memset(&cy, 0, sizeof(cy));
	cy.transform = make_obj_transform(cam_fwd_pos(gui, 3.0),
			vec3(0, 1, 0), vec3(0.5, 2.0, 0.5));
	cy.temp_color = vec3(0.9, 0.7, 0.4);
	scene_add_cylinder(gui->scene, cy);
	select_object(gui, TYPE_CYLINDER, gui->scene->cylinder_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_cone(t_gui *gui)
{
	t_cone	co;

	if (!gui->scene)
		return ;
	ft_memset(&co, 0, sizeof(co));
	co.transform = make_obj_transform(cam_fwd_pos(gui, 3.0),
			vec3(0, 1, 0), vec3(0.5, 2.0, 0.5));
	co.temp_color = vec3(0.9, 0.5, 0.3);
	scene_add_cone(gui->scene, co);
	select_object(gui, TYPE_CONE, gui->scene->cone_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_light(t_gui *gui)
{
	t_light	lt;
	t_vec3	pos;

	if (!gui->scene)
		return ;
	ft_memset(&lt, 0, sizeof(lt));
	pos = vec3_add(gui->cam_ctrl.transform.pos, vec3(0.0, 3.0, 0.0));
	lt.transform = make_obj_transform(pos, vec3(0, -1, 0), vec3(1, 1, 1));
	lt.rgb = vec3(1.0, 1.0, 1.0);
	lt.brightness = 0.8;
	lt.type = LIGHT_POINT;
	scene_add_light(gui->scene, lt);
	select_object(gui, TYPE_LIGHT, gui->scene->light_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

static void	delete_sel_sp_pl(t_scene *sc, t_selection *sel)
{
	int	i;

	i = sel->index;
	if (sel->type == TYPE_SPHERE && i < sc->sphere_count)
	{
		ft_memmove(sc->spheres + i, sc->spheres + i + 1,
			(sc->sphere_count - i - 1) * sizeof(t_sphere));
		sc->sphere_count--;
	}
	else if (sel->type == TYPE_PLANE && i < sc->plane_count)
	{
		ft_memmove(sc->planes + i, sc->planes + i + 1,
			(sc->plane_count - i - 1) * sizeof(t_plane));
		sc->plane_count--;
	}
}

static void	delete_sel_cy_co(t_scene *sc, t_selection *sel)
{
	int	i;

	i = sel->index;
	if (sel->type == TYPE_CYLINDER && i < sc->cylinder_count)
	{
		ft_memmove(sc->cylinders + i, sc->cylinders + i + 1,
			(sc->cylinder_count - i - 1) * sizeof(t_cylinder));
		sc->cylinder_count--;
	}
	else if (sel->type == TYPE_CONE && i < sc->cone_count)
	{
		ft_memmove(sc->cones + i, sc->cones + i + 1,
			(sc->cone_count - i - 1) * sizeof(t_cone));
		sc->cone_count--;
	}
}

void	editor_delete_selected(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	int			i;

	if (!gui->scene || !gui->selection.active)
		return ;
	sel = &gui->selection;
	sc = gui->scene;
	i = sel->index;
	if (sel->type == TYPE_LIGHT && i < sc->light_count)
	{
		ft_memmove(sc->lights + i, sc->lights + i + 1,
			(sc->light_count - i - 1) * sizeof(t_light));
		sc->light_count--;
	}
	else
	{
		delete_sel_sp_pl(sc, sel);
		delete_sel_cy_co(sc, sel);
	}
	clear_selection(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_obj(t_gui *gui, const char *path)
{
	int		mesh_start;
	int		i;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (!parse_obj(path, gui->scene))
		return ;
	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
		select_object(gui, TYPE_MESH, mesh_start);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_glb(t_gui *gui, const char *path)
{
	int		mesh_start;
	int		i;
	int		new_id;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (!parse_glb(path, gui->scene))
		return ;
	/* Mirror the .rt injection path:
	** 1. Bake identity world transform → sets edit_snap_verts,
	**    has_scene_transform and scene_mat so the animation system and the
	**    transform editor both work correctly.
	** 2. Clone materials so per-instance edits don't corrupt other meshes. */
	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		new_id = scene_clone_material(gui->scene,
			gui->scene->meshes[i].mat_id);
		if (new_id >= 0)
			gui->scene->meshes[i].mat_id = new_id;
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
		select_object(gui, TYPE_MESH, mesh_start);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
