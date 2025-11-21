/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 22:32:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "color.h"
# include "vectors.h"
# include <dirent.h>
# include <stdlib.h>

typedef enum e_map_style
{
	MAP_STYLE_DEFAULT,
	MAP_STYLE_GRADIENT,
	MAP_STYLE_SOLID,
	MAP_STYLE_ZEBRA,
	MAP_STYLE_NEON,
	MAP_STYLE_COUNT
}						t_map_style;

typedef struct s_map_style_config
{
	int					line_thickness;
	int					point_thickness;
	int					line_color;
	int					point_color;
	int					style;
}						t_map_style_config;

typedef struct s_map_points
{
	t_vec3d				**pos;
	t_vec3d				**raw;
	int					**color;
}						t_map_points;

typedef struct s_map
{
	int					width;
	int					height;
	t_vec2				min_max_z;
	int					min_proj_z;
	int					max_proj_z;
	double				z_divisor;
	t_map_points		points;
	t_map_style_config	style;
}						t_map;

typedef struct s_maps
{
	t_map				**maps;
	char				**map_files;
	int					count;
	int					current_index;
	t_map				*current_map;
}						t_maps;

t_map					*create_test_grid(void);
t_map					*load_map(char *filename);

int						get_solid_color(int z);
int						get_zebra_color(int z);
int						get_neon_color(int z);

void					free_map(t_map *map);
void					calculate_min_max_z(t_map *map);
void					init_map_list(t_maps *m);
void					load_map_files(t_maps *m, DIR *dir, int count);
void					cycle_map(t_maps *m);
void					apply_map_style(t_map *map);
int						get_map_line_color(t_vec3 v, t_map_style style);
void					cycle_map_style(t_maps *m);
int						allocate_map_points(t_map *map);
void					parse_map_data(t_map *map, int fd);
void					get_map_dimensions(int fd, int *width, int *height);
void					apply_colors(t_map *map);
void					recover_colors(t_map *map);

t_maps					init_maps(void);
t_map					*init_map(char *filename);
t_map					*select_initial_map(t_maps *manager);

#endif
