/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 18:47:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

extern const unsigned char	g_font5x7[95][5];

int	gfx_text_width(const char *s)
{
	int	n;

	n = 0;
	while (s && s[n])
		n++;
	return (n * 6);
}

void	gfx_text(t_app *app, int x, int y, const char *s, unsigned int rgba)
{
	int		i, row, ch;
	const unsigned char	*g;
	unsigned int *p;
	unsigned int color = rgba & 0x00FFFFFF;

	while (s && *s)
	{
		ch = (unsigned char)*s;
		if (ch < 32 || ch > 126) ch = '?';
		g = g_font5x7[ch - 32];
		for (i = 0; i < 5; i++)
		{
			for (row = 0; row < 7; row++)
			{
				if (g[i] & (1u << row))
				{
					int px = x + i;
					int py = y + row;
					if (px >= 0 && px < app->img.w && py >= 0 && py < app->img.h)
					{
						if (app->ui.scissor_y1 > 0 && (py < app->ui.scissor_y0 || py >= app->ui.scissor_y1))
							continue ;
						p = (unsigned int *)(app->img.addr + py * app->img.line_len + px * 4);
						*p = color;
					}
				}
			}
		}
		x += 6;
		s++;
	}
}