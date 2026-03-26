/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	editor_add_cone(t_gui *gui)
{
	t_cone	co;

	if (!gui->scene)
		return ;
	ft_memset(&co, 0, sizeof(co));
	co.transform = make_obj_transform(cam_fwd_pos(gui, 3.0), vec3(0, 1, 0),
			vec3(0.5, 2.0, 0.5));
	co.temp_color = vec3(0.9, 0.5, 0.3);
	scene_add_cone(gui->scene, co);
	select_object(gui, TYPE_CONE, gui->scene->cone_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
