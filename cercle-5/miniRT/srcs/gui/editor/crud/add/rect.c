/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:46:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	init_rect(t_rect *rc, t_vec3 pos)
{
	t_vec3	right;
	t_vec3	up;

	right = vec3(1, 0, 0);
	up = vec3(0, 1, 0);
	rc->v[0] = vec3_add(vec3_add(pos, vec3_scale(right, -1)), vec3_scale(up,
				-1));
	rc->v[1] = vec3_add(vec3_add(pos, vec3_scale(right, 1)), vec3_scale(up,
				-1));
	rc->v[2] = vec3_add(vec3_add(pos, vec3_scale(right, 1)), vec3_scale(up, 1));
	rc->v[3] = vec3_add(vec3_add(pos, vec3_scale(right, -1)), vec3_scale(up,
				1));
	rc->normal = vec3(0, 0, -1);
	rc->transform.pos = pos;
	rc->transform.scale = vec3(1, 1, 1);
	rc->phys.mass = 1.0;
	rc->phys.elasticity = 0.5;
	rc->phys.friction = 0.5;
	rc->temp_color = vec3(0.6, 0.8, 0.5);
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
	init_rect(&rc, pos);
	scene_add_rect(gui->scene, rc);
	select_object(gui, TYPE_RECT, gui->scene->rect_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}


