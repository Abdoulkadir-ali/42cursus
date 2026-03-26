/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Directly fills a row of pixels in the display buffer with a solid color.
 */
static void	fill_row(t_gui *gui, int x, int y, int w, unsigned int col)
{
	char	*dst;
	int		i;

	if (y < 0 || y >= gui->win.disp_h)
		return ;
	i = -1;
	while (++i < w)
	{
		if (x + i >= 0 && x + i < gui->win.disp_w)
		{
			dst = gui->win.disp_addr + (y * gui->win.disp_line_len + (x + i) * 4);
			*(unsigned int *)dst = col;
		}
	}
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
