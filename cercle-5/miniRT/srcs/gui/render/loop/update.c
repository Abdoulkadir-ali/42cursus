/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 14:26:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "map.h"
#include "profiler.h"
#include <stdlib.h>

#ifdef PROFILE_BUILD

static void	handle_profile_exit(t_gui *gui)
{
	int		max_frames;
	char	*bench_scale;

	gui->physics_enabled = false;
	bench_scale = getenv("BENCH_SCALE");
	if (bench_scale && atoi(bench_scale) >= 1)
		gui->render.scale = (size_t)atoi(bench_scale);
	max_frames = 22;
	if (getenv("BENCH_FRAMES"))
		max_frames = atoi(getenv("BENCH_FRAMES")) + 2;
	gui->render.dirty = true;
	gui->render.last_dirty = true;
	if (g_prof_frame >= max_frames)
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
	gui_map_update(gui);
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
