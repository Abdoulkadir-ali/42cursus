/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 02:55:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:53:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct t_vec2
{
	float	x;
	float	y;
}			t_vec2;

typedef struct t_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef struct s_vec2i
{
	int		x;
	int		y;
}			t_vec2i;

typedef struct s_vec3i
{
	int		x;
	int		y;
	int		z;
}			t_vec3i;

typedef struct s_vec2s
{
	size_t	x;
	size_t	y;
}			t_vec2s;

typedef struct s_vec3s
{
	size_t	x;
	size_t	y;
	size_t	z;
}			t_vec3s;

t_vec3		vec3(float x, float y, float z);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mul(t_vec3 a, t_vec3 b);
float		vec3_mag(t_vec3 a);
t_vec3		normalize_vec3(t_vec3 a);

#endif