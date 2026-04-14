/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "optimizations.h"

void	auto_fullres_toggle(t_gui *gui)
{
	gui->opts.auto_fullres = !gui->opts.auto_fullres;
	gui->render.dirty = true;
	gui->opts.prev_valid = false;
	if (gui->opts.auto_fullres)
		ft_print_debug("Auto Full-Res: ON\n");
	else
		ft_print_debug("Auto Full-Res: OFF\n");
}

void	adaptive_toggle(t_gui *gui)
{
	gui->opts.adaptive_scale = !gui->opts.adaptive_scale;
	if (gui->opts.adaptive_scale)
	{
		gui->render.scale = SCALE_MIN;
		gui->render.scale_last_change = now_ms();
	}
	gui->render.dirty = true;
	gui->opts.prev_valid = false;
	if (gui->opts.adaptive_scale)
		ft_print_debug("Adaptive Scale: ON\n");
	else
		ft_print_debug("Adaptive Scale: OFF\n");
}

/*
** time_pause_toggle: freezes or restores simulation time.
** Saves the current time_scale so resuming returns to the same speed.
*/
void	time_pause_toggle(t_gui *gui)
{
	static double	saved_scale = 1.0;
	double			*ts;

	ts = &gui->phys_engine.settings.time_scale;
	if (*ts > 1e-9)
	{
		saved_scale = *ts;
		*ts = 0.0;
		gui->anim_engine.time_scale = 0.0;
		ft_print_debug("Time: PAUSED\n");
	}
	else
	{
		*ts = saved_scale;
		gui->anim_engine.time_scale = saved_scale;
		ft_print_debug("Time: RESUMED\n");
	}
}

/*
** time_slower: halves the time_scale (minimum 1/16x speed).
*/
void	time_slower(t_gui *gui)
{
	double	*ts;

	ts = &gui->phys_engine.settings.time_scale;
	if (*ts < 1e-9)
		*ts = 0.0625;
	else
		*ts = *ts * 0.5;
	if (*ts < 0.0625)
		*ts = 0.0625;
	gui->anim_engine.time_scale = *ts;
	ft_print_debug("Time Scale: slow\n");
}

/*
** time_faster: doubles the time_scale (maximum 8x).
*/
void	time_faster(t_gui *gui)
{
	double	*ts;

	ts = &gui->phys_engine.settings.time_scale;
	if (*ts < 1e-9)
		*ts = 0.125;
	else
		*ts = *ts * 2.0;
	if (*ts > 8.0)
		*ts = 8.0;
	gui->anim_engine.time_scale = *ts;
	ft_print_debug("Time Scale: fast\n");
}
