/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	editor_add_cylinder(t_gui *gui)
{
	t_cylinder	cy;

	if (!gui->scene)
		return ;
	ft_memset(&cy, 0, sizeof(cy));
	cy.transform = make_obj_transform(cam_fwd_pos(gui, 3.0), vec3(0, 1, 0),
			vec3(0.5, 2.0, 0.5));
	cy.temp_color = vec3(0.9, 0.7, 0.4);
	scene_add_cylinder(gui->scene, cy);
	select_object(gui, TYPE_CYLINDER, gui->scene->cylinder_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
