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
#include "debug.h"

void	editor_add_cone(t_gui *gui)
{
	t_prim_params	params;

	if (!gui->scene)
		return ;
	ft_memset(&params, 0, sizeof(params));
	params.pos = cam_fwd_pos(gui, 3.0);
	params.axis = vec3(0, 1, 0);
	params.radius = 0.5;
	params.height = 2.0;
	params.mat_id = scene_add_material_from_color(gui->scene,
			vec3(0.9, 0.5, 0.3));
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_cone: pos=(%.2f,%.2f,%.2f)\n",
		(double)params.pos.x, (double)params.pos.y, (double)params.pos.z);
	pthread_rwlock_wrlock(&gui->scene_lock);
	scene_add_primitive(gui->scene, params, PRIM_CONE);
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_cone: prim count now=%zu\n",
		gui->scene->primitives.count);
	select_object(gui, TYPE_CONE, gui->scene->primitives.count - 1);
	rebuild_bvh(gui);
	pthread_rwlock_unlock(&gui->scene_lock);
	gui->render.dirty = true;
}
