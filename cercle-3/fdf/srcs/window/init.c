/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:06:55 by abdoali          ###   ########.fr       */
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

int	init_window_main_image(t_window *win, void *mlx)
{
	t_image	*main_img;

	main_img = &win->main_img;
	main_img->img = mlx_new_image(mlx, win->width, win->height);
	if (!main_img->img)
		return (0);
	main_img->img_addr = mlx_get_data_addr(main_img->img, &main_img->img_bpp,
			&main_img->img_line_len, &main_img->img_endian);
	if (!main_img->img_addr)
		return (0);
	win->z_buffer = malloc(sizeof(float) * win->width * win->height);
	if (!win->z_buffer)
		return (0);
	return (1);
}

int	init_window_system(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->window = init_window(data->mlx_ptr);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window->width,
			data->window->height, "FDF - Advanced Controls");
	if (!data->win_ptr)
		return (0);
	data->window->ptr = data->win_ptr;
	return (1);
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
