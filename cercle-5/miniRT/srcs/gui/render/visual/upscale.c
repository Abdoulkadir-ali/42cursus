/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:53:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Nearest-neighbor upscale from render image to display image.
** Maps each display pixel back to the corresponding render pixel.
*/
static void	upscale_nn(t_gui *gui)
{
	t_vec2i			p;
	uint32_t		*src_row;
	uint32_t		*dst_row;
	int				sy;

	p.y = 0;
	while (p.y < gui->win.disp_size.y)
	{
		sy = (p.y * gui->win.size.y) / gui->win.disp_size.y;
		src_row = (uint32_t *)(gui->win.addr + sy * gui->win.line_len);
		dst_row = (uint32_t *)(gui->win.disp_addr + 
			p.y * gui->win.disp_line_len);
		p.x = 0;
		while (p.x < gui->win.disp_size.x)
		{
			dst_row[p.x] = src_row[(p.x * gui->win.size.x) / 
				gui->win.disp_size.x];
			p.x++;
		}
		p.y++;
	}
}

static void	blit_direct(t_gui *gui)
{
	memcpy(gui->win.disp_addr, gui->win.addr,
		gui->win.disp_size.y * gui->win.disp_line_len);
}

void	upscale_image(t_gui *gui)
{
	if (gui->win.size.x == gui->win.disp_size.x
		&& gui->win.size.y == gui->win.disp_size.y)
	{
		blit_direct(gui);
		return ;
	}
	upscale_nn(gui);
}
