/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:05:22 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:30:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	glyph_pixel_on(const unsigned char *glyph, int row, int col)
{
	return (((glyph[row] >> (7 - col)) & 1) != 0);
}

static void	draw_glyph_pixel(t_gui *gui, t_vec2i screen, unsigned int color)
{
	unsigned int	*px;

	if (screen.x >= gui->win.disp_size.x)
		return ;
	if (screen.y >= gui->win.disp_size.y)
		return ;
	px = (unsigned int *)(gui->win.disp_addr + screen.y * gui->win.disp_line_len
			+ screen.x * (gui->win.disp_bpp / 8));
	*px = color;
}

void	draw_char(t_gui *gui, unsigned char c, t_vec2i pos, unsigned int color)
{
	const unsigned char	*glyph;
	t_vec2i				screen;
	int					row;

	if (c < 32 || c > 126)
		return ;
	glyph = gui->font[c - 32];
	row = 0;
	while (row < 8)
	{
		screen.y = pos.y + row;
		if (screen.y < gui->win.disp_size.y)
		{
			screen.x = pos.x;
			while (screen.x < pos.x + 8)
			{
				if (glyph_pixel_on(glyph, row, screen.x - pos.x))
					draw_glyph_pixel(gui, screen, color);
				screen.x++;
			}
		}
		row++;
	}
}
