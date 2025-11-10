#include "fdf.h"
#include "gui.h"
#include "projection.h"

static int	is_point_visible(t_point p3d, t_data *data)
{
	int		relief;

	if (data->camera.dampening_threshold <= 0)
		return (1);
	relief = p3d.pos.z;
	if (relief < 0)
		relief = -relief;
	return (relief >= data->camera.dampening_threshold);
}

static int	is_on_screen(int x, int y, t_data *data)
{
	return (x >= -100 && x < data->win_width + 100
		&& y >= -100 && y < data->win_height + 100);
}

static int	should_draw_line(t_point p1, t_point p2, t_data *data)
{
	return (is_on_screen(p1.pos.x, p1.pos.y, data)
		|| is_on_screen(p2.pos.x, p2.pos.y, data));
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
				if (should_draw_line(p1, p2, data))
					draw_line(data, p1, p2);
			}
			if (y < data->map->height - 1
				&& is_point_visible(data->map->points[y + 1][x], data))
			{
				p2 = project_point(data->map->points[y + 1][x], data->camera,
						data->camera.projection);
				if (should_draw_line(p1, p2, data))
					draw_line(data, p1, p2);
			}
			x++;
		}
		y++;
	}
}

static void	clear_image(t_data *data)
{
	memset(data->img_addr, 0, data->win_height * data->img_line_len);
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
