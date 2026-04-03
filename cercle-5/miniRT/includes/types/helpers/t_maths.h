/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_maths.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:49:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_HELPERS_MATHS_H
# define TYPES_HELPERS_MATHS_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct s_vec2i
{
	int								x;
	int								y;
}									t_vec2i;

typedef struct s_vec3i
{
	int								x;
	int								y;
	int								z;
	int								w;
}									t_vec3i;

typedef struct s_vec2
{
	double							x;
	double							y;
}									t_vec2;

typedef struct s_vec3
{
	double							x;
	double							y;
	double							z;
	double							w;
}									t_vec3;

typedef struct s_vec4
{
	double							x;
	double							y;
	double							z;
	double							w;
}									t_vec4;

typedef struct s_mat4
{
	double							m[4][4];
}									t_mat4;

typedef struct s_rotator
{
	double							pitch;
	double							yaw;
	double							roll;
}									t_rotator;

typedef struct s_transform
{
	t_vec3							pos;
	t_rotator						rotation;
	t_vec3							scale;
	t_vec3							forward;
	t_vec3							right;
	t_vec3							up;
}									t_transform;

typedef struct s_aabb
{
	t_vec3							min;
	t_vec3							max;
}									t_aabb;

typedef struct s_ray
{
	t_vec3							origin;
	t_vec3							direction;
	t_vec3							inv_dir;
	int								sign[3];
	size_t							depth;
	double							weight;
}									t_ray;

typedef struct s_quadratic
{
	double							a;
	double							b;
	double							c;
}									t_quadratic;

typedef struct s_quadratic_roots
{
	double							t1;
	double							t2;
}									t_quadratic_roots;

#endif
