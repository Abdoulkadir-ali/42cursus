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

#include "editor.h"
#include "debug.h"

void	editor_add_rect(t_gui *gui)
{
	t_prim_params	params;

	if (!gui->scene)
		return ;
	ft_memset(&params, 0, sizeof(params));
	params.pos = cam_fwd_pos(gui, 3.0);
	params.axis = vec3(0, 0, -1);
	params.tangent = vec3(1, 0, 0);
	params.extents = vec3(2.0, 2.0, 0);
	params.mat_id = scene_add_material_from_color(gui->scene,
			vec3(0.6, 0.8, 0.5));
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_rect: pos=(%.2f,%.2f,%.2f)\n",
		(double)params.pos.x, (double)params.pos.y, (double)params.pos.z);
	pthread_rwlock_wrlock(&gui->scene_lock);
	scene_add_primitive(gui->scene, params, PRIM_RECT);
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_rect: prim count now=%zu\n",
		gui->scene->primitives.count);
	select_object(gui, TYPE_RECT, gui->scene->primitives.count - 1);
	rebuild_bvh(gui);
	pthread_rwlock_unlock(&gui->scene_lock);
	gui->render.dirty = true;
}


