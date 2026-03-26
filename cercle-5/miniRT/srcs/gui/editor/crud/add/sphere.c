/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	editor_add_sphere(t_gui *gui)
{
	t_sphere	sp;

	if (!gui->scene)
		return ;
	ft_memset(&sp, 0, sizeof(sp));
	sp.transform = make_obj_transform(cam_fwd_pos(gui, 3.0), vec3(0, 0, -1),
			vec3(1, 1, 1));
	sp.temp_color = vec3(0.7, 0.7, 0.9);
	sp.radius_sq = 1.0;
	scene_add_sphere(gui->scene, sp);
	select_object(gui, TYPE_SPHERE, gui->scene->sphere_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
