/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:11:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdlib.h>
# include "color.h"
# include "vectors.h"

typedef enum e_map_style
{
	MAP_STYLE_DEFAULT,
	MAP_STYLE_COUNT
}			t_map_style;

typedef struct s_map_render_config
{
	int		line_thickness;
	int		point_thickness;
	int		line_color;
	int		point_color;
	int		style;
}			t_map_render_config;

typedef struct s_map
{
	int		width;
	int		height;
	int		min_z;
	int		max_z;
	double	z_divisor;
	t_point	**points;
}			t_map;

typedef struct s_map_manager
{
    t_map   **maps;
    char    **map_files;
    int     count;
    int     current_index;
}           t_map_manager;



t_map		*create_test_grid(void);
t_map		*load_map(char *filename);
void		free_map(t_map *map);
void		calculate_min_max_z(t_map *map);
void		init_map_list(t_data *data);
void		cycle_map(t_data *data);
void		apply_map_style(t_data *data);
int			get_map_line_color(t_vec3 v, t_map_style style);
void		cycle_map_style(t_data *data);

#endif
