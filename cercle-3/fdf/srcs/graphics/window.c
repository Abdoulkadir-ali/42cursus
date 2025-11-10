#include "fdf.h"
#include "gui.h"
#include "projection.h"

static int	is_point_visible(t_point p3d, t_data *data)
{
	if (data->camera.dampening_threshold <= data->map->min_z)
		return (1);
	return (p3d.pos.z >= data->camera.dampening_threshold);
}

void	draw_grid(t_data *data)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (!is_point_visible(data->map->points[y][x], data))
			{
				x++;
				continue ;
			}
			p1 = project_point(data->map->points[y][x], data->camera,
					data->camera.projection);
			if (x < data->map->width - 1
				&& is_point_visible(data->map->points[y][x + 1], data))
			{
				p2 = project_point(data->map->points[y][x + 1], data->camera,
						data->camera.projection);
				draw_line(data, p1, p2);
			}
			if (y < data->map->height - 1
				&& is_point_visible(data->map->points[y + 1][x], data))
			{
				p2 = project_point(data->map->points[y + 1][x], data->camera,
						data->camera.projection);
				draw_line(data, p1, p2);
			}
			x++;
		}
		y++;
	}
}

static void	clear_image(t_data *data)
{
	int	total_bytes;

	total_bytes = data->win_height * data->img_line_len;
	memset(data->img_addr, 0, total_bytes);
}

void	redraw(t_data *data)
{
	update_zoom(data);
	clear_image(data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->gui_img, 0, 0);
	render_gui(data);
}
