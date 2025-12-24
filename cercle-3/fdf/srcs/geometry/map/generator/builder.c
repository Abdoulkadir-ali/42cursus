/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:18:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

static void	fill_map(int **map, t_gen_params params, t_noise_state *noise)
{
	t_vec2	pos;
	float	val;

	pos.y = 0;
	while (pos.y < params.height)
	{
		pos.x = 0;
		while (pos.x < params.width)
		{
			val = get_octave_noise((float)pos.x / params.width, (float)pos.y
					/ params.height, params, noise);
			map[pos.y][pos.x] = (int)(val * params.z_scale);
			pos.x++;
		}
		pos.y++;
	}
}

int	**generate_heightmap(t_gen_params params)
{
	int				**map;
	t_noise_state	*noise;

	noise = init_noise(params.seed);
	if (!noise)
		return (NULL);
	map = allocate_map(params.height, params.width);
	if (!map)
	{
		free(noise);
		return (NULL);
	}
	fill_map(map, params, noise);
	free(noise);
	return (map);
}
