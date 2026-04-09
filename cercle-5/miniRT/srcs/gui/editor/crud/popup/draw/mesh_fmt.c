/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_popup_mesh_fmt(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	m_h;
	int		bw;

	d = gui->win.disp_size;
	m_h = ui_sy(POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, m_h, &o);
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
		o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Add Mesh");
	bw = ui_sx((POPUP_W - POPUP_PAD * 3) / 2, d);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD, d),
			o.y + ui_sy(36 + POPUP_PAD, d)),
		ui_size(bw, POPUP_ITEM_H, d), COL_CRUD_BTN_BG, COL_BORDER, "OBJ"});
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + bw,
			o.y + ui_sy(36 + POPUP_PAD, d)),
		ui_size(bw, POPUP_ITEM_H, d), COL_CRUD_BTN_BG, COL_BORDER, "GLB"});
}
