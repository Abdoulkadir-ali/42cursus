/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:36:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vectors.h"

typedef struct s_point
{
	t_vec3	pos;
	int		color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		min_z;
	int		max_z;
	double	z_divisor;
	t_point	**points;
}	t_map;

typedef struct s_data	t_data;

t_map	*create_test_grid(void);
t_map	*load_map(char *filename);
void	free_map(t_map *map);
void	calculate_min_max_z(t_map *map);
void	init_map_list(t_data *data);
void	cycle_map(t_data *data);

#endif
