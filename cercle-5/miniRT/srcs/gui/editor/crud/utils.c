/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_crud_btn(t_gui *gui, t_panel btn)
{
	t_vec2s	d;

	d = gui->win.disp_size;
	draw_panel(gui, btn);
	if (btn.lbl && *btn.lbl)
		mlx_string_put_c(gui->win.mlx, gui->win.win,
			btn.pos.x + ui_sx(8, d),
			btn.pos.y + btn.size.y / 2 + ui_sy(4, d),
			COL_TEXT, (char *)btn.lbl);
}
