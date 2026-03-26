/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
