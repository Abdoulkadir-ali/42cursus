/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_style.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:36:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STYLE_H
# define MAP_STYLE_H

typedef enum e_map_style
{
	MAP_STYLE_GRADIENT,
	MAP_STYLE_SOLID,
	MAP_STYLE_ZEBRA,
	MAP_STYLE_NEON,
	MAP_STYLE_COUNT
}	t_map_style;

typedef struct s_map_render_config
{
	int			line_thickness;
	int			point_thickness;
	int			line_color;
	int			point_color;
	t_map_style	style;
}	t_map_render_config;

void	cycle_map_style(struct s_data *data);
void	apply_map_style(struct s_data *data);
int		get_map_line_color(int z, int min_z, int max_z, t_map_style style);
int		get_map_point_color(int z, int min_z, int max_z, t_map_style style);

#endif
