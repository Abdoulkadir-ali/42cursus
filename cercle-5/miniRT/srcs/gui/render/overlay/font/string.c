/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:18:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_char(t_gui *gui, unsigned char c, int x, int y, unsigned int color);

/*
** Draw a NUL-terminated string into disp_img.
** Multi-byte UTF-8 lead bytes (>0x7E) are consumed and skipped.
** Each ASCII glyph advances the cursor by 8 pixels.
*/
void	gui_draw_string(t_gui *gui, const char *str, int x, int y,
unsigned int color)
{
	int		cx;
	unsigned char	c;

	if (!gui || !str)
		return ;
	cx = x;
	while (*str)
	{
		c = (unsigned char)*str;
		if (c > 0x7E)
		{
			/* skip multi-byte UTF-8: count continuation bytes */
			str++;
			while ((*str & 0xC0) == 0x80)
				str++;
			continue ;
		}
		draw_char(gui, c, cx, y, color);
		cx += 8;
		str++;
	}
}
