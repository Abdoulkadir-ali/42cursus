/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:04:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	skip_utf8(const char **str)
{
	(*str)++;
	while ((**str & 0xC0) == 0x80)
		(*str)++;
}

/*
** Draw a NUL-terminated string into disp_img using t_vec2i position.
*/
void	gui_draw_string(t_gui *gui, const char *str, t_vec2i pos,
		unsigned int color)
{
	t_vec2i			curr;
	unsigned char	c;

	if (!gui || !str)
		return ;
	curr = pos;
	while (*str)
	{
		c = (unsigned char)*str;
		if (c > 0x7E)
		{
			skip_utf8(&str);
			continue ;
		}
		draw_char(gui, c, curr, color);
		curr.x += 8;
		str++;
	}
}
