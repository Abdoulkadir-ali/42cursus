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

void	editor_add_tri(t_gui *gui)
{
	t_tri_shape	tr;
	t_vec3		pos;
	t_vec3		e1;
	t_vec3		e2;

	if (!gui->scene)
		return ;
	pos = cam_fwd_pos(gui, 3.0);
	ft_memset(&tr, 0, sizeof(tr));
	tr.v[0] = vec3_add(pos, vec3(-1, -1, 0));
	tr.v[1] = vec3_add(pos, vec3(1, -1, 0));
	tr.v[2] = vec3_add(pos, vec3(0, 1, 0));
	tr.temp_color = vec3(0.6, 0.5, 0.9);
	e1 = vec3_sub(tr.v[1], tr.v[0]);
	e2 = vec3_sub(tr.v[2], tr.v[0]);
	tr.normal = vec3_norm(vec3_cross(e1, e2));
	scene_add_tri(gui->scene, tr);
	select_object(gui, TYPE_TRI, gui->scene->tri_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
