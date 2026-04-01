/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ambient_panel(t_gui *gui, t_vec2i pos)
{
	t_islider	sl[4];

	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + 8, 88, COL_HOVER, "AMBIENT LIGHT");
	get_ambient_sliders(gui->scene, sl);
	draw_panel_sliders(gui, sl, 4, (t_vec2i){pos.x + 8, 104});
}
