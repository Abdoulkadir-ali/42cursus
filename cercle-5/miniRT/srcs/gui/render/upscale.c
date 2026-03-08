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
	unsigned int	*src_row;
	unsigned int	*dst_row;

	if (gui->win.width == gui->win.disp_w && gui->win.height == gui->win.disp_h)
	{
		ft_memcpy(gui->win.disp_addr, gui->win.addr,
			(size_t)gui->win.disp_h * (size_t)gui->win.disp_line_len);
		return ;
	}
	y = 0;
	while (y < gui->win.disp_h)
	{
		src_row = (unsigned int *)(gui->win.addr
				+ (y * gui->win.height / gui->win.disp_h)
				* gui->win.line_len);
		dst_row = (unsigned int *)(gui->win.disp_addr
				+ y * gui->win.disp_line_len);
		x = 0;
		while (x < gui->win.disp_w)
		{
			dst_row[x] = src_row[x * gui->win.width / gui->win.disp_w];
			x++;
		}
		y++;
	}
}
