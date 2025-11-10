#include "fdf.h"
#include "gui.h"
#include "projection.h"

static void	init_window_size(t_data *data)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(data->mlx_ptr, &screen_w, &screen_h);
	data->win_width = (int)(screen_w * WINDOW_WIDTH_RATIO);
	data->win_height = (int)(screen_h * WINDOW_HEIGHT_RATIO);
	if (data->win_width < MIN_WINDOW_WIDTH)
		data->win_width = MIN_WINDOW_WIDTH;
	if (data->win_height < MIN_WINDOW_HEIGHT)
		data->win_height = MIN_WINDOW_HEIGHT;
	if (data->win_width > screen_w)
		data->win_width = screen_w;
	if (data->win_height > screen_h)
		data->win_height = screen_h;
}

static void	init_camera(t_data *data)
{
	data->camera.rotation.x = 0;
	data->camera.rotation.y = 0;
	data->camera.rotation.z = 0;
	data->camera.scale = 20;
	data->camera.target_scale = 20;
	data->camera.offset.x = data->win_width / 2;
	data->camera.offset.y = data->win_height / 2;
	data->camera.color_shift.red = 0;
	data->camera.color_shift.blue = 0;
	data->camera.color_shift.green = 0;
	data->camera.move_speed = 1.0;
	data->camera.zoom_speed = 1.0;
	data->camera.projection = PROJ_ISOMETRIC;
	data->camera.dampening_threshold = 0.0;
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
	init_camera(&data);
	init_mouse(&data);
	init_keys(&data);
	data.buttons = init_buttons();
	data.map = create_test_grid();
	if (!data.map)
		return (1);
	data.img = mlx_new_image(data.mlx_ptr, data.win_width, data.win_height);
	data.img_addr = mlx_get_data_addr(data.img, &data.img_bpp,
			&data.img_line_len, &data.img_endian);
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
