/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:11:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

void	editor_add_capsule(t_gui *gui)
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
			vec3(255.0, 255.0, 255.0));
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_capsule: pos=(%.2f,%.2f,%.2f)\n",
		(double)params.pos.x, (double)params.pos.y, (double)params.pos.z);
	pthread_rwlock_wrlock(&gui->scene_lock);
	scene_add_primitive(gui->scene, params, PRIM_CAPSULE);
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_capsule: prim count now=%zu\n",
		gui->scene->primitives.count);
	select_object(gui, TYPE_CAPSULE, gui->scene->primitives.count - 1);
	rebuild_bvh(gui);
	pthread_rwlock_unlock(&gui->scene_lock);
	gui->render.dirty = true;
}
