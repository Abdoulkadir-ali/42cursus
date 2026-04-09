/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
	gui->render.bvh_needs_rebuild = 1;
}

void	editor_add_rect(t_gui *gui)
{
	t_rect	rc;

	if (!gui->scene)
		return ;
	ft_memset(&rc, 0, sizeof(rc));
	rc.transform.pos = cam_fwd_pos(gui, 3.0);
	rc.v[0] = vec3_add(vec3_add(rc.transform.pos,
				vec3_scale(vec3(1, 0, 0), -1)), vec3_scale(vec3(0, 1, 0), -1));
	rc.v[1] = vec3_add(vec3_add(rc.transform.pos,
				vec3_scale(vec3(1, 0, 0), 1)), vec3_scale(vec3(0, 1, 0), -1));
	rc.v[2] = vec3_add(vec3_add(rc.transform.pos,
				vec3_scale(vec3(1, 0, 0), 1)), vec3_scale(vec3(0, 1, 0), 1));
	rc.v[3] = vec3_add(vec3_add(rc.transform.pos,
				vec3_scale(vec3(1, 0, 0), -1)), vec3_scale(vec3(0, 1, 0), 1));
	rc.normal = vec3(0, 0, -1);
	rc.transform.scale = vec3(1, 1, 1);
	rc.phys.mass = 1.0;
	rc.phys.elasticity = 0.5;
	rc.phys.friction = 0.5;
	rc.temp_color = vec3(0.6, 0.8, 0.5);
	scene_add_rect(gui->scene, rc);
	select_object(gui, TYPE_RECT, gui->scene->rect_count - 1);
	gui->render.bvh_needs_rebuild = 1;
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
	gui->render.bvh_needs_rebuild = 1;
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
	gui->render.bvh_needs_rebuild = 1;
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
	gui->render.bvh_needs_rebuild = 1;
}
