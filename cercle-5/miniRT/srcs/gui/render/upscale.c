/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Nearest-neighbor upscale from render image to display image.
** Maps each display pixel back to the corresponding render pixel.
*/
void	upscale_image(t_gui *gui)
{
	int				y;
	int				x;
	int				src_x;
	int				err;
	unsigned int	*src_row;
	unsigned int	*dst_row;

	if (gui->win.size.x == gui->win.disp_size.x && gui->win.size.y == gui->win.disp_size.y)
	{
		memcpy(gui->win.disp_addr, gui->win.addr,
			(size_t)gui->win.disp_size.y * (size_t)gui->win.disp_line_len);
		return ;
	}
	y = 0;
	while (y < gui->win.disp_size.y)
	{
		src_row = (unsigned int *)(gui->win.addr
				+ (y * gui->win.size.y / gui->win.disp_size.y)
				* gui->win.line_len);
		dst_row = (unsigned int *)(gui->win.disp_addr
				+ y * gui->win.disp_line_len);
		x = 0;
		src_x = 0;
		err = 0;
		while (x < gui->win.disp_size.x)
		{
			dst_row[x] = src_row[src_x];
			err += gui->win.size.x;
			while (err >= gui->win.disp_size.x)
			{
				src_x++;
				err -= gui->win.disp_size.x;
			}
			x++;
		}
		y++;
	}
}
