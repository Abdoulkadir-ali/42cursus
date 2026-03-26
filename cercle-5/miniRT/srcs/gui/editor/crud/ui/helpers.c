/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl)
{
	t_transform	tr;

	ft_memset(&tr, 0, sizeof(tr));
	tr.pos = pos;
	tr.forward = fwd;
	tr.scale = scl;
	return (tr);
}

t_vec3	cam_fwd_pos(t_gui *gui, double dist)
{
	return (vec3_add(gui->cam_ctrl.transform.pos,
			vec3_scale(gui->cam_ctrl.transform.forward, dist)));
}
