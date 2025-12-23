/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:17 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:14:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "geometry.h"

typedef struct s_height_color_ctx
{
	double			ratio;
	double			shift;
	double			effective_z;
	double			max_effective;
}					t_height_color_ctx;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

int					clamp(int value, int min, int max);
double				clamp_d(double value, double min, double max);

t_vec3				int_color_to_rgb(unsigned int color);
unsigned int		rgb_to_int(t_vec3 color);

t_vec3				create_color(int r, int g, int b);
unsigned int		create_color_rgb(t_vec3 rgb);
t_vec3				shift_color(t_vec3 color, t_vec3 shift);
t_vec3				create_color_wrap(int r, int g, int b);

t_vec3				interpolate_color(t_vec3 color1, t_vec3 color2,
						double ratio);
t_vec3				get_height_color(double z, int min_z, int max_z);

#endif
