/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:55:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_info_row(t_gui *gui, t_vec2i pos, const char *label,
		const char *val)
{
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, pos.y, COL_HOVER,
		(char *)label);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 96, pos.y, COL_TEXT,
		(char *)val);
}
