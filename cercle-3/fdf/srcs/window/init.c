/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 20:58:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_window	init_window(void *mlx_ptr)
{
	t_window win;
	int screen_w;
	int screen_h;
	int calculated_w;
	int calculated_h;

	mlx_get_screen_size(mlx_ptr, &screen_w, &screen_h);
	calculated_w = (int)(screen_w * WINDOW_WIDTH_RATIO);
	calculated_h = (int)(screen_h * WINDOW_HEIGHT_RATIO);
	if (calculated_w < MIN_WINDOW_WIDTH)
		win.width = MIN_WINDOW_WIDTH;
	else if (calculated_w > MAX_WINDOW_WIDTH)
		win.width = MAX_WINDOW_WIDTH;
	else
		win.width = calculated_w;
	if (calculated_h < MIN_WINDOW_HEIGHT)
		win.height = MIN_WINDOW_HEIGHT;
	else if (calculated_h > MAX_WINDOW_HEIGHT)
		win.height = MAX_WINDOW_HEIGHT;
	else
		win.height = calculated_h;
	if (win.width > screen_w - 50)
		win.width = screen_w - 50;
	if (win.height > screen_h - 50)
		win.height = screen_h - 50;
	win.mlx_ptr = mlx_ptr;
	win.ptr = NULL;
	win.main_img.img = NULL;
	win.main_img.img_addr = NULL;
	win.main_img.img_bpp = 0;
	win.main_img.img_line_len = 0;
	win.main_img.img_endian = 0;
	win.gui_img.img = NULL;
	win.gui_img.img_addr = NULL;
	win.gui_img.img_bpp = 0;
	win.gui_img.img_line_len = 0;
	win.gui_img.img_endian = 0;
	win.z_buffer = NULL;
	return (win);
}