/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:37:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Directly fills a row of pixels in the display buffer with a solid color.
 */
static void	fill_row(t_gui *gui, int x, int y, int w, unsigned int col)
{
	unsigned int	*row;
	int				x0;
	int				x1;
	int				stride;

	if (y < 0 || y >= gui->win.disp_size.y)
		return ;
	x0 = x;
	if (x < 0)
		x0 = 0;
	x1 = x + w;
	if (x1 > gui->win.disp_size.x)
		x1 = gui->win.disp_size.x;
	if (x0 >= x1)
		return ;
	stride = gui->win.disp_line_len / 4;
	row = (unsigned int *)gui->win.disp_addr + y * stride;
	while (x0 < x1)
		row[x0++] = col;
}

/**
 * @brief Directly fills a rectangular area with a solid color (no transparency).
 * Optimized for small UI elements like sliders.
 */
void	fill_rect(t_gui *gui, int x, int y, int w, int h, unsigned int col)
{
	int	j;

	j = -1;
	while (++j < h)
		fill_row(gui, x, y + j, w, col);
}
