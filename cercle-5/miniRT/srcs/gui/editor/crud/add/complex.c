/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:55:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl);

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
