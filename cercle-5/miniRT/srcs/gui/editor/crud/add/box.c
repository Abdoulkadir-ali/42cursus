/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
