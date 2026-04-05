/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 21:05:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl)
{
	t_transform	tr;

	ft_memset(&tr, 0, sizeof(tr));
	tr.pos = pos;
	tr.forward = fwd;
	tr.scale = scl;
	return (tr);
}

t_vec3	cam_fwd_pos(t_gui *gui, double dist)
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
	sp.inv_scale = vec3(1, 1, 1);
	scene_add_sphere(gui->scene, sp);
	select_object(gui, TYPE_SPHERE, gui->scene->sphere_count - 1);
	gui->render.bvh_needs_rebuild = 1;
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
	gui->render.bvh_needs_rebuild = 1;
}
