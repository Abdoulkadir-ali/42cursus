/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	editor_add_plane(t_gui *gui)
{
	t_plane	pl;

	if (!gui->scene)
		return ;
	ft_memset(&pl, 0, sizeof(pl));
	pl.transform = make_obj_transform(cam_fwd_pos(gui, 3.0), vec3(0, 1, 0),
			vec3(1, 1, 1));
	pl.temp_color = vec3(0.5, 0.5, 0.55);
	scene_add_plane(gui->scene, pl);
	select_object(gui, TYPE_PLANE, gui->scene->plane_count - 1);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
