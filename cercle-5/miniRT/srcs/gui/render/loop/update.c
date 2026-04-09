/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 16:49:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#ifdef PROFILE_BUILD

static void	handle_profile_exit(t_gui *gui)
{
	static int	prof_frames = 0;

	if (++prof_frames > 5)
		mlx_loop_end(gui->win.mlx);
}

#else

static void	handle_profile_exit(t_gui *gui)
{
	(void)gui;
}

#endif

int	gui_update(t_gui *gui)
{
	double	delta;

	delta = update_delta(gui);
	handle_profile_exit(gui);
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
