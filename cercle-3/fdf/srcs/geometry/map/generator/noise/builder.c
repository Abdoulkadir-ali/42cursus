/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:58:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 23:58:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

static float	get_octave_noise(float x, float y, t_gen_params p)
{
	float	total;
	float	frequency;
	float	amplitude;
	float	max_value;
	int		i;

	total = 0;
	frequency = 1;
	amplitude = 1;
	max_value = 0;
	i = 0;
	while (i < p.octaves)
	{
		total += perlin2d(x * p.scale * frequency,
				y * p.scale * frequency, 0, 0) * amplitude;
		max_value += amplitude;
		amplitude *= p.persistence;
		frequency *= 2;
		i++;
	}
	// Normalize to 0..1 range (approx) then center
	return ((total / max_value) + 0.5f);
}

int	**generate_heightmap(t_gen_params params)
{
	int		**map;
	int		x;
	int		y;
	float	val;

	init_noise(params.seed);
	map = (int **)malloc(sizeof(int *) * params.height);
	if (!map)
		return (NULL);
	y = 0;
	while (y < params.height)
	{
		map[y] = (int *)malloc(sizeof(int) * params.width);
		if (!map[y])
		{
			// Cleanup previous rows
			while (--y >= 0)
				free(map[y]);
			free(map);
			return (NULL);
		}
		x = 0;
		while (x < params.width)
		{
			val = get_octave_noise((float)x / params.width,
					(float)y / params.height, params);
			map[y][x] = (int)(val * params.z_scale);
			x++;
		}
		y++;
	}
	return (map);
}

void	free_heightmap(int **map, int height)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < height)
	{
		free(map[y]);
		y++;
	}
	free(map);
}
