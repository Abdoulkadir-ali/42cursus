/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:17 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 22:33:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "geometry.h"

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}		t_rgb;

int				clamp(int value, int min, int max);
double			clamp_d(double value, double min, double max);
unsigned char	get_red(unsigned int color);
unsigned char	get_green(unsigned int color);
unsigned char	get_blue(unsigned int color);
t_vec3			get_color_vec3(unsigned int color);

unsigned int	create_color(unsigned char r, unsigned char g, unsigned char b);
unsigned int	create_color_rgb(t_vec3 rgb);
unsigned int	shift_color(unsigned int color, int r_shift, int g_shift, int b_shift);
unsigned int	create_color_wrap(int r, int g, int b);

unsigned int	interpolate_color(unsigned int color1, unsigned int color2, double ratio);
unsigned int	get_height_color(double z, int min_z, int max_z);

#endif
