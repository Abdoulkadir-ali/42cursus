/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 20:16:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_vec2i		p;
	t_vec2s		d;

	d = gui->win.disp_size;
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(92, d);
	if (click_mat_slots(gui, mouse, &p))
		return (true);
	if (click_fdf_row(gui, mouse, &p))
		return (true);
	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	if (click_mat_surface(gui, mouse, mat, &p))
		return (true);
	if (click_mat_albedo(gui, mouse, mat, &p))
		return (true);
	if (click_mat_emission(gui, mouse, mat, &p))
		return (true);
	return (false);
}
