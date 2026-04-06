/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
	size_t	s;

	gui->render.force_fullres = !gui->render.force_fullres;
	if (!gui->render.force_fullres)
	{
		s = (size_t)(gui->settings.render_scale + 0.5);
		if (s < 1)
			s = 1;
		if (s > 8)
			s = 8;
		gui->render.scale = s;
	}
	gui->render.dirty = true;
}
