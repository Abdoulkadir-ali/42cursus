/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:53:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"
#include "projection.h"
#include "events.h"
#include <stdio.h>
#include <sys/time.h>

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, cleanup_and_exit, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, mouse_press, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
}

static int	init_mlx_and_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	init_window_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
			data->win_height, "FDF - Advanced Controls");
	if (!data->win_ptr)
		return (0);
	return (1);
}

static int	init_map_and_image(t_data *data)
{
	init_map_list(data);
	if (data->map_count > 0)
		data->map = data->maps[0];
	else
		data->map = create_test_grid();
	if (!data->map)
		return (0);
	data->img = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	if (!data->img)
		return (0);
	data->img_addr = mlx_get_data_addr(data->img, &data->img_bpp,
			&data->img_line_len, &data->img_endian);
	if (!data->img_addr)
		return (0);
	return (1);
}

static int	init_and_render(t_data *data)
{
	init_camera(data);
	apply_map_style(data);
	if (!init_gui(data))
		return (0);
	draw_panel_background(data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->gui_img, 0, 0);
	render_gui(data);
	return (1);
}

int	main(void)
{
	t_data			data;
	struct timeval	tv;

	if (!init_mlx_and_window(&data))
		return (1);
	init_mouse(&data);
	init_keys(&data);
	init_map_config(&data);
	gettimeofday(&tv, NULL);
	data.last_frame_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data.frame_in_progress = 0;
	data.lod_level = DEFAULT_LOD_LEVEL;
	data.render_mode = RENDER_LINES;
	data.camera.use_z_divisor = 1;
	if (!init_map_and_image(&data))
		return (1);
	if (!init_and_render(&data))
		return (1);
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
