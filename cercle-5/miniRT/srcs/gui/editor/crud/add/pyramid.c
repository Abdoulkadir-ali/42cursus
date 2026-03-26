/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 15:59:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
