/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "optimizations.h"

void	map_next_press(t_gui *gui)
{
	gui_next_map(gui);
}

void	map_prev_press(t_gui *gui)
{
	gui_prev_map(gui);
}

void	exit_press(t_gui *gui)
{
	gui->render.abort_render = 1;
	mlx_loop_end(gui->win.mlx);
}

void	fullres_toggle(t_gui *gui)
{
	gui->render.force_fullres = !gui->render.force_fullres;
	if (gui->render.force_fullres)
		gui->render.scale = 1;
	gui->render.dirty = true;
	gui->opts.prev_valid = false;
	if (gui->render.force_fullres)
		ft_print_debug("Force FullRes: ON\n");
	else
		ft_print_debug("Force FullRes: OFF\n");
}

void	bake_toggle(t_gui *gui)
{
	if (gui->render.bake_job && gui->render.bake_job->running)
		bake_job_cancel(gui);
	else
		bake_job_start(gui);
}
