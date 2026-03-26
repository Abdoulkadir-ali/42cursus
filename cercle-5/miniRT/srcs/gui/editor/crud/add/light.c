/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:39:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
