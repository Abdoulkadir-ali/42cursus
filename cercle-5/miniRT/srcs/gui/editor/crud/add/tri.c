/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

void	editor_add_tri(t_gui *gui)
{
	t_vec3		v[3];
	t_vec3		pos;
	int			mat_id;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	v[0] = vec3_add(pos, vec3(-1, -1, 0));
	v[1] = vec3_add(pos, vec3(1, -1, 0));
	v[2] = vec3_add(pos, vec3(0, 1, 0));
	mat_id = scene_add_material_from_color(gui->scene, vec3(0.6, 0.5, 0.9));
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_tri: pos=(%.2f,%.2f,%.2f)\n",
		(double)pos.x, (double)pos.y, (double)pos.z);
	pthread_rwlock_wrlock(&gui->scene_lock);
	scene_add_tri(gui->scene, v, mat_id);
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_add_tri: prim count now=%zu\n",
		gui->scene->tri_soa.count);
	select_object(gui, TYPE_TRI, gui->scene->tri_soa.count - 1);
	rebuild_bvh(gui);
	pthread_rwlock_unlock(&gui->scene_lock);
	gui->render.dirty = true;
}
