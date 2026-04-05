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
	gui->render.force_fullres = !gui->render.force_fullres;
	gui->render.dirty = true;
}
