/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:40:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_window	init_window(void *mlx_ptr)
{
	t_window	window;

	window.mlx_ptr = mlx_ptr;
	window.ptr = NULL;
	window.width = 0;
	window.height = 0;
	window.main_img.img = NULL;
	window.main_img.img_addr = NULL;
	window.main_img.img_bpp = 0;
	window.main_img.img_line_len = 0;
	window.main_img.img_endian = 0;
	window.gui_img.img = NULL;
	window.gui_img.img_addr = NULL;
	window.gui_img.img_bpp = 0;
	window.gui_img.img_line_len = 0;
	window.gui_img.img_endian = 0;
	window.z_buffer = NULL;
	return (window);
}

void	init_mouse(t_mouse *mouse)
{
	mouse->left_pressed = 0;
	mouse->right_pressed = 0;
	mouse->middle_pressed = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->middle_start_x = 0;
	mouse->middle_start_y = 0;
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
	keys->ctrl_left = 0;
	keys->ctrl_right = 0;
	keys->shift_left = 0;
	keys->shift_right = 0;
	keys->l = 0;
	keys->z = 0;
	keys->f = 0;
	keys->h = 0;
	keys->d = 0;
	keys->t = 0;
	keys->s = 0;
	keys->a = 0;
	keys->x = 0;
	keys->i = 0;
	keys->v = 0;
	keys->g = 0;
}

void	init_map_config(t_data *data)
{
	data->graphics.map_config.line_thickness = 1;
	data->graphics.map_config.point_thickness = 0;
	data->graphics.map_config.line_color = 0xFFFFFF;
	data->graphics.map_config.point_color = 0xFFFFFF;
	data->graphics.map_config.style = 0;
}

void	init_window_size(t_data *data)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	data->window.width = screen_width * WINDOW_WIDTH_RATIO;
	data->window.height = screen_height * WINDOW_HEIGHT_RATIO;
	if (data->window.width < MIN_WINDOW_WIDTH)
		data->window.width = MIN_WINDOW_WIDTH;
	if (data->window.height < MIN_WINDOW_HEIGHT)
		data->window.height = MIN_WINDOW_HEIGHT;
	if (data->window.width > MAX_WINDOW_WIDTH)
		data->window.width = MAX_WINDOW_WIDTH;
	if (data->window.height > MAX_WINDOW_HEIGHT)
		data->window.height = MAX_WINDOW_HEIGHT;
}
