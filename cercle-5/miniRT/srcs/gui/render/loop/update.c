/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:48:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	gui_update(t_gui *gui)
{
	double	delta;

#ifdef PROFILE_BUILD
	static int	_prof_frames = 0;
	if (++_prof_frames > 5)
		mlx_loop_end(gui->win.mlx);
#endif
	delta = update_delta(gui);
	cmd_drain(gui);
	scene_swap_step(gui);
	physics_step(gui, delta);
	anim_step(gui, delta);
	gui_update_input(gui);
	bvh_step(gui);
	if (gui->render.dirty || gui->render.last_dirty)
	{
		raytrace_step(gui, delta);
		gui->render.last_dirty = gui->render.dirty;
		gui->render.dirty = false;
	}
	return (0);
}
