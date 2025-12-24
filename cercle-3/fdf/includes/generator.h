/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:50:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 02:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include "geometry.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <time.h>

typedef struct s_gen_params
{
	int			width;
	int			height;
	float		scale;
	int			octaves;
	float		persistence;
	float		z_scale;
	int			seed;
}				t_gen_params;

typedef struct s_noise_state
{
	int			perm[512];
	t_vec2d		grads[256];
}				t_noise_state;

typedef struct s_interp_params
{
	t_vec2d		fade_vals;
	float		x;
	float		y;
}				t_interp_params;

/* parser.c */
int				ft_atoi_safe(const char *str);
float			ft_atof(const char *str);

/* noise.c */
t_noise_state	*init_noise(int seed);
float			perlin2d(t_noise_state *state, t_vec2d pos);
float			noise_at(t_noise_state *state, float x, float y);

/* interpolate.c */
float			fade(float t);
float			lerp(float t, float a, float b);
t_vec2d			lerp_vec(float t, t_vec2d a, t_vec2d b);
float			grad(t_noise_state *state, int hash, float x, float y);

/* builder.c */
int				**generate_heightmap(t_gen_params params);
void			free_heightmap(int **map, int height);

/* writer.c */
void			save_map_to_file(int **map, int w, int h, char *filename);

/* runtime.c */
struct s_map	*generate_runtime_map(t_gen_params params);

#endif
