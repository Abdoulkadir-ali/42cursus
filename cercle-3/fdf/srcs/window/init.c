/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:52:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_window_images(t_window *win)
{
	win->main_img.img = NULL;
	win->main_img.img_addr = NULL;
	win->main_img.img_bpp = 0;
	win->main_img.img_line_len = 0;
	win->main_img.img_endian = 0;
	win->gui_img.img = NULL;
	win->gui_img.img_addr = NULL;
	win->gui_img.img_bpp = 0;
	win->gui_img.img_line_len = 0;
	win->gui_img.img_endian = 0;
	win->z_buffer = NULL;
}

t_window	*init_window(void *mlx_ptr)
{
	t_window	*win;
	int			screen_w;
	int			screen_h;
	int			calculated_w;
	int			calculated_h;

	win = malloc(sizeof(t_window));
	if (!win)
		return (NULL);
	mlx_get_screen_size(mlx_ptr, &screen_w, &screen_h);
	calculated_w = (int)(screen_w * WINDOW_WIDTH_RATIO);
	calculated_h = (int)(screen_h * WINDOW_HEIGHT_RATIO);
	win->width = clamp(calculated_w, MIN_WINDOW_WIDTH, MAX_WINDOW_WIDTH);
	if (win->width > screen_w - 50)
		win->width = screen_w - 50;
	win->height = clamp(calculated_h, MIN_WINDOW_HEIGHT, MAX_WINDOW_HEIGHT);
	if (win->height > screen_h - 50)
		win->height = screen_h - 50;
	win->mlx_ptr = mlx_ptr;
	win->ptr = NULL;
	init_window_images(win);
	return (win);
}
