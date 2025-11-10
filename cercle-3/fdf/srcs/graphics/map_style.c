/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 16:40:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map_style.h"

static int	get_gradient_color(int z, int min_z, int max_z)
{
	double	ratio;
	int		r;
	int		g;
	int		b;

	if (max_z == min_z)
		return (0xFFFFFF);
	ratio = (double)(z - min_z) / (double)(max_z - min_z);
	r = (int)(255 * ratio);
	g = (int)(100 + 155 * ratio);
	b = (int)(255 * (1.0 - ratio));
	return ((r << 16) | (g << 8) | b);
}

static int	get_solid_color(int z)
{
	if (z > 0)
		return (0xFF6B35);
	else if (z < 0)
		return (0x004E89);
	return (0xFFFFFF);
}

static int	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (0xFFFFFF);
	return (0x00FFFF);
}

static int	get_neon_color(int z)
{
	int	colors[5];
	int	index;

	colors[0] = 0xFF00FF;
	colors[1] = 0x00FFFF;
	colors[2] = 0xFFFF00;
	colors[3] = 0xFF0080;
	colors[4] = 0x00FF80;
	if (z < 0)
		z = -z;
	index = z % 5;
	return (colors[index]);
}

int	get_map_line_color(int z, int min_z, int max_z, t_map_style style)
{
	if (style == MAP_STYLE_GRADIENT)
		return (get_gradient_color(z, min_z, max_z));
	else if (style == MAP_STYLE_SOLID)
		return (get_solid_color(z));
	else if (style == MAP_STYLE_ZEBRA)
		return (get_zebra_color(z));
	else if (style == MAP_STYLE_NEON)
		return (get_neon_color(z));
	return (0xFFFFFF);
}

int	get_map_point_color(int z, int min_z, int max_z, t_map_style style)
{
	return (get_map_line_color(z, min_z, max_z, style));
}

void	cycle_map_style(t_data *data)
{
	data->map_config.style = (data->map_config.style + 1) % MAP_STYLE_COUNT;
	apply_map_style(data);
}

void	apply_map_style(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			data->map->points[y][x].color = get_map_line_color(
					data->map->points[y][x].pos.z,
					data->map->min_z,
					data->map->max_z,
					data->map_config.style);
			x++;
		}
		y++;
	}
}
