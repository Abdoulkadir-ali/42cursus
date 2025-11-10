/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"
#include "projection.h"

int	is_point_visible(t_point p3d, t_data *data)
{
	int		threshold;
	int		z;

	threshold = data->camera.dampening_threshold;
	if (threshold == 0)
		return (1);
	z = p3d.pos.z;
	if (threshold < 0)
		return (z >= -threshold);
	else
		return (z <= threshold);
}

int	is_on_screen(int x, int y, t_data *data)
{
	int	margin;

	margin = data->camera.frustum_margin;
	return (x >= -margin && x < data->win_width + margin
		&& y >= -margin && y < data->win_height + margin);
}

static int	is_point_in_frustum(t_point p, t_data *data)
{
	return (is_on_screen(p.pos.x, p.pos.y, data));
}

int	should_draw_line(t_point p1, t_point p2, t_data *data)
{
	if (!is_point_in_frustum(p1, data) && !is_point_in_frustum(p2, data))
	{
		if ((p1.pos.x < 0 && p2.pos.x < 0)
			|| (p1.pos.x > data->win_width && p2.pos.x > data->win_width)
			|| (p1.pos.y < 0 && p2.pos.y < 0)
			|| (p1.pos.y > data->win_height && p2.pos.y > data->win_height))
			return (0);
	}
	return (1);
}

void	clear_image(t_data *data)
{
	memset(data->img_addr, 0, data->win_height * data->img_line_len);
}

void	clear_z_buffer(t_data *data)
{
	int	i;
	int	total;

	if (!data->z_buffer)
		return ;
	total = data->win_width * data->win_height;
	i = 0;
	while (i < total)
	{
		data->z_buffer[i] = 1e30f;
		i++;
	}
}

int		z_buffer_test(t_data *data, int x, int y, float z)
{
	int	index;

	if (!data->use_depth_culling || !data->z_buffer)
		return (1);
	if (x < 0 || x >= data->win_width || y < 0 || y >= data->win_height)
		return (0);
	index = y * data->win_width + x;
	if (z < data->z_buffer[index])
	{
		data->z_buffer[index] = z;
		return (1);
	}
	return (0);
}
