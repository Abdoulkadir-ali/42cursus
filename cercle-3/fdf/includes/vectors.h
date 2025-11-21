/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 22:32:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "libft.h"
# include <math.h>
# include <xmmintrin.h>

typedef struct s_vec2
{
	int		x;
	int		y;
}			t_vec2;

typedef struct s_vec2d
{
	double	x;
	double	y;
}			t_vec2d;

typedef struct s_vec3
{
	int		x;
	int		y;
	int		z;
}			t_vec3;

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}			t_vec3d;

typedef struct s_vec4d
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vec4d;

typedef struct s_point
{
	t_vec3d	pos;
	int		color;
}			t_point;

t_vec2		create_vec2(int x, int y);
t_vec2d		create_vec2d(double x, double y);
t_vec3		create_vec3(int x, int y, int z);
t_vec3d		create_vec3d(double x, double y, double z);

void		vec2_add(t_vec2 *self, t_vec2 other);
void		vec2_sub(t_vec2 *self, t_vec2 other);
void		vec2_multiply(t_vec2 *self, t_vec2 other);
void		vec2_divide(t_vec2 *self, t_vec2 other);
void		vec2_multiply_scalar(t_vec2 *self, int scalar);

int			vec2_len(t_vec2 v);
int			vec2_min(t_vec2 v);
int			vec2_max(t_vec2 v);
t_vec2		vec2_minmax(int min, int max);

void		vec2d_add(t_vec2d *self, t_vec2d other);
void		vec2d_sub(t_vec2d *self, t_vec2d other);
void		vec2d_multiply(t_vec2d *self, t_vec2d other);
void		vec2d_divide(t_vec2d *self, t_vec2d other);
void		vec2d_multiply_scalar(t_vec2d *self, double scalar);

double		vec2d_len(t_vec2d v);
double		vec2d_min(t_vec2d v);
double		vec2d_max(t_vec2d v);
t_vec2d		vec2d_minmax(int min, int max);

void		vec3_add(t_vec3 *self, t_vec3 other);
void		vec3_sub(t_vec3 *self, t_vec3 other);
void		vec3_multiply(t_vec3 *self, t_vec3 other);
void		vec3_divide(t_vec3 *self, t_vec3 other);
void		vec3_multiply_scalar(t_vec3 *self, int scalar);

double		vec3_len(t_vec3 v);
double		vec3_min(t_vec3 v);
double		vec3_max(t_vec3 v);
t_vec2		vec3_get_minmax_components(t_vec3 v);

void		vec3d_add(t_vec3d *self, t_vec3d other);
void		vec3d_sub(t_vec3d *self, t_vec3d other);
void		vec3d_multiply(t_vec3d *self, t_vec3d other);
void		vec3d_divide(t_vec3d *self, t_vec3d other);
void		vec3d_multiply_scalar(t_vec3d *self, double scalar);

double		vec3d_len(t_vec3d v);
double		vec3d_min(t_vec3d v);
double		vec3d_max(t_vec3d v);
t_vec2d		vec3d_minmax(t_vec3d v);
#endif
