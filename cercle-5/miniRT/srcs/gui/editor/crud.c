/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 07:26:02 by abdoali          ###   ########.fr       */
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
	else if (sel->type == TYPE_TRI && i < sc->tri_count)
	{
		ft_memmove(sc->tris + i, sc->tris + i + 1,
			(sc->tri_count - i - 1) * sizeof(t_tri_shape));
		sc->tri_count--;
	}
	else if (sel->type == TYPE_RECT && i < sc->rect_count)
	{
		ft_memmove(sc->rects + i, sc->rects + i + 1,
			(sc->rect_count - i - 1) * sizeof(t_rect));
		sc->rect_count--;
	}
	else if (sel->type == TYPE_PYRAMID && i < sc->pyramid_count)
	{
		ft_memmove(sc->pyramids + i, sc->pyramids + i + 1,
			(sc->pyramid_count - i - 1) * sizeof(t_pyramid));
		sc->pyramid_count--;
	}
	else if (sel->type == TYPE_BOX && i < sc->box_count)
	{
		ft_memmove(sc->boxes + i, sc->boxes + i + 1,
			(sc->box_count - i - 1) * sizeof(t_box));
		sc->box_count--;
	}
	else if (sel->type == TYPE_CAPSULE && i < sc->capsule_count)
	{
		ft_memmove(sc->capsules + i, sc->capsules + i + 1,
			(sc->capsule_count - i - 1) * sizeof(t_capsule));
		sc->capsule_count--;
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

void	editor_add_tri(t_gui *gui)
{
	t_tri_shape	tr;
	t_vec3		pos;
	t_vec3		e1;
	t_vec3		e2;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&tr, 0, sizeof(tr));
	tr.v[0] = vec3_add(pos, vec3(-1, -1, 0));
	tr.v[1] = vec3_add(pos, vec3(1, -1, 0));
	tr.v[2] = vec3_add(pos, vec3(0, 1, 0));
	tr.temp_color = vec3(0.6, 0.5, 0.9);
	e1 = vec3_sub(tr.v[1], tr.v[0]);
	e2 = vec3_sub(tr.v[2], tr.v[0]);
	tr.normal = vec3_norm(vec3_cross(e1, e2));
	scene_add_tri(gui->scene, tr);
	select_object(gui, TYPE_TRI, gui->scene->tri_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_rect(t_gui *gui)
{
	t_rect	rc;
	t_vec3	pos;
	t_vec3	right;
	t_vec3	up;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&rc, 0, sizeof(rc));
	right = vec3(1, 0, 0);
	up = vec3(0, 1, 0);
	rc.v[0] = vec3_add(vec3_add(pos, vec3_scale(right, -1)),
			vec3_scale(up, -1));
	rc.v[1] = vec3_add(vec3_add(pos, vec3_scale(right, 1)),
			vec3_scale(up, -1));
	rc.v[2] = vec3_add(vec3_add(pos, vec3_scale(right, 1)),
			vec3_scale(up, 1));
	rc.v[3] = vec3_add(vec3_add(pos, vec3_scale(right, -1)),
			vec3_scale(up, 1));
	rc.normal = vec3(0, 0, -1);
	rc.transform.pos = pos;
	rc.transform.scale = vec3(1, 1, 1);
	rc.phys.mass = 1.0;
	rc.phys.elasticity = 0.5;
	rc.phys.friction = 0.5;
	rc.temp_color = vec3(0.6, 0.8, 0.5);
	scene_add_rect(gui->scene, rc);
	select_object(gui, TYPE_RECT, gui->scene->rect_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_pyramid(t_gui *gui)
{
	t_pyramid	py;
	t_vec3		pos;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&py, 0, sizeof(py));
	py.transform.pos = pos;
	py.transform.scale = vec3(1, 1, 1);
	py.up = vec3(0, 1, 0);
	py.base_size = 2.0;
	py.height = 2.0;
	py.phys.mass = 1.0;
	py.phys.elasticity = 0.5;
	py.phys.friction = 0.5;
	py.temp_color = vec3(0.9, 0.6, 0.3);
	scene_add_pyramid(gui->scene, py);
	select_object(gui, TYPE_PYRAMID, gui->scene->pyramid_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_box(t_gui *gui)
{
	t_box	bx;
	t_vec3	pos;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&bx, 0, sizeof(bx));
	bx.transform.pos = pos;
	bx.transform.forward = vec3(1, 0, 0);
	bx.transform.scale = vec3(1, 1, 1);
	bx.half_extents = vec3(1.0, 1.0, 1.0);
	bx.phys.mass = 1.0;
	bx.phys.elasticity = 0.5;
	bx.phys.friction = 0.5;
	bx.temp_color = vec3(0.4, 0.7, 0.9);
	scene_add_box(gui->scene, bx);
	select_object(gui, TYPE_BOX, gui->scene->box_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_capsule(t_gui *gui)
{
	t_capsule	cap;
	t_vec3		pos;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&cap, 0, sizeof(cap));
	cap.transform.pos = pos;
	cap.transform.scale = vec3(1, 1, 1);
	cap.axis = vec3(0, 1, 0);
	cap.radius = 0.5;
	cap.half_height = 1.0;
	cap.phys.mass = 1.0;
	cap.phys.elasticity = 0.5;
	cap.phys.friction = 0.5;
	cap.temp_color = vec3(0.8, 0.4, 0.7);
	scene_add_capsule(gui->scene, cap);
	select_object(gui, TYPE_CAPSULE, gui->scene->capsule_count - 1);
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
	{
		scene_add_group_for_subs(gui->scene, path, mesh_start);
		select_object(gui, TYPE_MESH, gui->scene->group_count - 1);
	}
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_glb(t_gui *gui, const char *path)
{
	int		mesh_start;
	int		i;
	int		new_id;
	int		gid;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (mesh_cache_has(path))
	{
		/* Geometry already parsed: restore from cache (avoids re-parsing) */
		if (!mesh_cache_restore(path, gui->scene))
			return ;
		/* Cache restore doesn't know about group IDs — assign a fresh one */
		gid = gui->scene->mesh_group_count++;
		i = mesh_start;
		while (i < gui->scene->mesh_count)
			gui->scene->meshes[i++].group_id = gid;
	}
	else
	{
		/* First import: full parse; parse_glb assigns group_id internally */
		if (!parse_glb(path, gui->scene))
			return ;
		mesh_cache_save(path, gui->scene, mesh_start);
	}
	/* For every new submesh:
	** 1. Bake an identity world transform so edit_snap_verts captures real
	**    vertex positions (parse_glb zeros transform.scale via memset —
	**    passing that directly would collapse all vertices to the origin).
	** 2. Clone materials so per-instance edits are isolated. */
	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		gui->scene->meshes[i].transform = (t_transform){0};
		gui->scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		new_id = scene_clone_material(gui->scene,
			gui->scene->meshes[i].mat_id);
		if (new_id >= 0)
			gui->scene->meshes[i].mat_id = new_id;
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
	{
		scene_add_group_for_subs(gui->scene, path, mesh_start);
		select_object(gui, TYPE_MESH, gui->scene->group_count - 1);
	}
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
