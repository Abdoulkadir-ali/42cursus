/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

void	settings_init(t_gui *gui)
{
	gui->settings.visible = false;
	gui->settings.tab = STAB_RAYTRACER;
	gui->settings.render_scale = gui->render.scale;
	gui->settings.solver_iters
		= (double)gui->phys_engine.settings.solver_iterations;
	gui->settings.pos = vec2i(
			gui->win.disp_size.x - SETTINGS_W - 16, 30);
	gui->settings.dragging = false;
}

void	settings_open(t_gui *gui)
{
	gui->settings.render_scale = gui->render.scale;
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
	t_vec2i	p;

	if (!gui->settings.dragging)
		return ;
	p.x = mouse.x - gui->settings.drag_offset.x;
	p.y = mouse.y - gui->settings.drag_offset.y;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	if (p.x > gui->win.disp_size.x - SETTINGS_W)
		p.x = gui->win.disp_size.x - SETTINGS_W;
	if (p.y > gui->win.disp_size.y - SETTINGS_H)
		p.y = gui->win.disp_size.y - SETTINGS_H;
	gui->settings.pos = p;
	gui->render.dirty = true;
}

void	settings_end_drag(t_gui *gui)
{
	gui->settings.dragging = false;
}
