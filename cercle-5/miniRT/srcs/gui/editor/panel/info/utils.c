/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_info_row(t_gui *gui, t_vec2i pos, const char *label,
		const char *val)
{
	t_vec2i	d;

	d = gui->win.disp_size;
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), pos.y,
		COL_HOVER, (char *)label);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(96, d), pos.y,
		COL_TEXT, (char *)val);
}
