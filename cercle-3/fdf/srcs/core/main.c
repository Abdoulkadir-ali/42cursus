#include "fdf.h"
#include "gui.h"
#include "projection.h"
#include "events.h"
#include <stdio.h>

static void	init_window_size(t_data *data)
{
	int	screen_w;
	int	screen_h;
	int	calculated_w;
	int	calculated_h;

	mlx_get_screen_size(data->mlx_ptr, &screen_w, &screen_h);
	calculated_w = (int)(screen_w * WINDOW_WIDTH_RATIO);
	calculated_h = (int)(screen_h * WINDOW_HEIGHT_RATIO);
	if (calculated_w < MIN_WINDOW_WIDTH)
		data->win_width = MIN_WINDOW_WIDTH;
	else if (calculated_w > MAX_WINDOW_WIDTH)
		data->win_width = MAX_WINDOW_WIDTH;
	else
		data->win_width = calculated_w;
	if (calculated_h < MIN_WINDOW_HEIGHT)
		data->win_height = MIN_WINDOW_HEIGHT;
	else if (calculated_h > MAX_WINDOW_HEIGHT)
		data->win_height = MAX_WINDOW_HEIGHT;
	else
		data->win_height = calculated_h;
	if (data->win_width > screen_w - 50)
		data->win_width = screen_w - 50;
	if (data->win_height > screen_h - 50)
		data->win_height = screen_h - 50;
}

static void	init_camera(t_data *data)
{
	data->camera.move_speed = 1.0;
	data->camera.zoom_speed = 1.0;
	data->camera.projection = PROJ_ISOMETRIC;
	data->camera.gui_style = 0;
	adjust_camera_to_map(data);
}

static void	init_map_config(t_data *data)
{
	data->map_config.line_thickness = 1;
	data->map_config.point_thickness = 0;
	data->map_config.line_color = 0xFFFFFF;
	data->map_config.point_color = 0xFFFFFF;
	data->map_config.style = 0;
}

static void	init_mouse(t_data *data)
{
	data->mouse.left_pressed = 0;
	data->mouse.right_pressed = 0;
	data->mouse.middle_pressed = 0;
	data->mouse.last_x = 0;
	data->mouse.last_y = 0;
	data->mouse.middle_start_x = 0;
	data->mouse.middle_start_y = 0;
}

static void	init_keys(t_data *data)
{
	data->keys.up = 0;
	data->keys.down = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.ctrl_left = 0;
	data->keys.ctrl_right = 0;
}

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

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	init_window_size(&data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win_width,
			data.win_height, "FDF - Advanced Controls");
	if (!data.win_ptr)
		return (1);
	init_mouse(&data);
	init_keys(&data);
	init_map_config(&data);
	data.buttons = init_buttons();
	init_map_list(&data);
	if (data.map_count > 0)
		data.map = data.maps[0];
	else
		data.map = create_test_grid();
	if (!data.map)
		return (1);
	data.img = mlx_new_image(data.mlx_ptr, data.win_width, data.win_height);
	data.img_addr = mlx_get_data_addr(data.img, &data.img_bpp,
			&data.img_line_len, &data.img_endian);
	init_camera(&data);
	apply_map_style(&data);
	init_gui(&data);
	draw_panel_background(&data);
	draw_grid(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.gui_img, 0, 0);
	render_gui(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
