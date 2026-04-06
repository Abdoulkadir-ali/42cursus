/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:17:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

void	settings_init(t_gui *gui)
{
	gui->settings.visible = false;
	gui->settings.tab = STAB_RAYTRACER;
	gui->settings.render_scale = (double)gui->render.scale;
	gui->settings.solver_iters
		= (double)gui->phys_engine.settings.solver_iterations;
	gui->settings.pos = vec2i(
			(int)gui->win.disp_size.x - SETTINGS_W - 16, 30);
	gui->settings.dragging = false;
}

void	settings_open(t_gui *gui)
{
	gui->settings.render_scale = (double)gui->render.scale;
	gui->settings.solver_iters
		= (double)gui->phys_engine.settings.solver_iterations;
	gui->settings.visible = true;
	gui->render.dirty = true;
}

void	settings_close(t_gui *gui)
{
	gui->settings.visible = false;
	gui->render.dirty = true;
}

void	settings_handle_drag(t_gui *gui, t_vec2i mouse)
{
	int	nx;
	int	ny;

	if (!gui->settings.dragging)
		return ;
	nx = (int)mouse.x - (int)gui->settings.drag_offset.x;
	ny = (int)mouse.y - (int)gui->settings.drag_offset.y;
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	if (nx > (int)gui->win.disp_size.x - SETTINGS_W)
		nx = (int)gui->win.disp_size.x - SETTINGS_W;
	if (ny > (int)gui->win.disp_size.y - SETTINGS_H)
		ny = (int)gui->win.disp_size.y - SETTINGS_H;
	gui->settings.pos = vec2i(nx, ny);
	gui->render.dirty = true;
}

void	settings_end_drag(t_gui *gui)
{
	gui->settings.dragging = false;
}
