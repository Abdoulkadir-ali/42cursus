/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:49:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "define.h"
# include <math.h>

/* ========== VECTORS ========== */

typedef struct s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct s_vec3
{
	int				x;
	int				y;
	int				z;
}					t_vec3;

typedef struct s_vec3d
{
	double			x;
	double			y;
	double			z;
}					t_vec3d;

typedef struct s_vecu2
{
	unsigned int	x;
	unsigned int	y;
}					t_vecu2;

typedef struct s_vecu3
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}					t_vecu3;

typedef struct s_point
{
	t_vec3d			pos;
	t_vec3			color;
}					t_point;

/* Vector Constructors */
t_vec2				create_vec2(int x, int y);
t_vec2d				create_vec2d(double x, double y);
t_vec3				create_vec3(int x, int y, int z);
t_vec3d				create_vec3d(double x, double y, double z);

/* Vector Operations */
void				vec2_add(t_vec2 *self, t_vec2 other);
void				vec2_sub(t_vec2 *self, t_vec2 other);
void				vec2_multiply(t_vec2 *self, t_vec2 other);
void				vec2_divide(t_vec2 *self, t_vec2 other);

void				vec2_multiply_scalar(t_vec2 *self, int scalar);
int					vec2_len(t_vec2 v);
int					vec2_min(t_vec2 v);
int					vec2_max(t_vec2 v);

void				vec2d_add(t_vec2d *self, t_vec2d other);
void				vec2d_sub(t_vec2d *self, t_vec2d other);
void				vec2d_multiply(t_vec2d *self, t_vec2d other);
void				vec2d_divide(t_vec2d *self, t_vec2d other);
void				vec2d_multiply_scalar(t_vec2d *self, double scalar);
double				vec2d_len(t_vec2d v);

double				vec3_len(t_vec3 v);
void				vec3_add(t_vec3 *self, t_vec3 other);
void				vec3_sub(t_vec3 *self, t_vec3 other);
void				vec3_multiply(t_vec3 *self, t_vec3 other);
void				vec3_divide(t_vec3 *self, t_vec3 other);
void				vec3_multiply_scalar(t_vec3 *self, int scalar);

void				vec3d_add(t_vec3d *self, t_vec3d other);
void				vec3d_sub(t_vec3d *self, t_vec3d other);
void				vec3d_multiply(t_vec3d *self, t_vec3d other);
void				vec3d_divide(t_vec3d *self, t_vec3d other);
void				vec3d_multiply_scalar(t_vec3d *self, double scalar);

/* Unsigned Vectors */
t_vecu2				create_vecu2(unsigned int x, unsigned int y);
t_vecu3				create_vecu3(unsigned int x, unsigned int y,
						unsigned int z);

void				vecu2_add(t_vecu2 *self, t_vecu2 other);
void				vecu2_sub(t_vecu2 *self, t_vecu2 other);
void				vecu2_multiply(t_vecu2 *self, t_vecu2 other);
void				vecu2_divide(t_vecu2 *self, t_vecu2 other);
void				vecu2_multiply_scalar(t_vecu2 *self, unsigned int scalar);

void				vecu3_add(t_vecu3 *self, t_vecu3 other);
void				vecu3_sub(t_vecu3 *self, t_vecu3 other);
void				vecu3_multiply(t_vecu3 *self, t_vecu3 other);
void				vecu3_divide(t_vecu3 *self, t_vecu3 other);
void				vecu3_multiply_scalar(t_vecu3 *self, unsigned int scalar);

/* Distance / Utils */
unsigned int		vecu2_len(t_vecu2 v);
unsigned int		vecu2_min(t_vecu2 v);
unsigned int		vecu2_max(t_vecu2 v);

unsigned int		vecu3_len(t_vecu3 v);
unsigned int		vecu3_min(t_vecu3 v);
unsigned int		vecu3_max(t_vecu3 v);

/* ========== CLAMP ========== */

void				clamp_float(float *value, float min, float max);
void				clamp_double(double *value, double min, double max);
void				clamp_uint(unsigned int *value, unsigned int min,
						unsigned int max);
int					clamp(int value, int min, int max);
double				clamp_d(double value, double min, double max);
void				clamp_color(t_vec3 *color, int min, int max);

#endif