/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:50:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 23:50:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include "libft.h"
# include "geometry.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>

typedef struct s_gen_params
{
	int		width;
	int		height;
	float	scale;
	int		octaves;
	float	persistence;
	float	z_scale;
	int		seed;
}			t_gen_params;

/* noise.c */
void	init_noise(int seed);
float	perlin2d(float x, float y, float freq, int depth);
float	noise_at(float x, float y);

/* builder.c */
int		**generate_heightmap(t_gen_params params);
void	free_heightmap(int **map, int height);

/* writer.c */
void	save_map_to_file(int **map, int w, int h, char *filename);

/* runtime.c */
struct s_map	*generate_runtime_map(t_gen_params params);

#endif
