/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dod.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 11:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:10:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# include "objects.h"

/* 
 * SCRATCH STRUCTS:
 * These are used as temporary stack bridges between the SoA storage 
 * (t_primitive_array) and the geometric math logic.
 * They are NOT stored long-term.
 */

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	int		mat_idx;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	int		mat_idx;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	axis;
	double	radius;
	double	height;
	int		mat_idx;
}	t_cylinder;

typedef struct s_cone
{
	t_vec3	tip;
	t_vec3	axis;
	double	angle;
	double	height;
	int		mat_idx;
}	t_cone;

typedef struct s_box
{
	t_vec3	min;
	t_vec3	max;
	int		mat_idx;
}	t_box;

typedef struct s_capsule
{
	t_vec3	a;
	t_vec3	b;
	double	radius;
	int		mat_idx;
}	t_capsule;

typedef struct s_rect
{
	t_vec3	pos;
	t_vec3	normal;
	double	ex;
	double	ey;
	int		mat_idx;
}	t_rect_scratch;

typedef struct s_pyramid
{
	t_vec3	pos;
	t_vec3	up;
	double	size;
	double	height;
	int		mat_idx;
}	t_pyramid;

typedef struct s_tri_view
{
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_vec3		n;
	uint16_t	mat_idx;
}	t_tri_view;

/* PROTOTYPES */
t_sphere	unpack_sphere(const t_primitive_array *p, int i);
t_plane		unpack_plane(const t_primitive_array *p, int i);
t_cylinder	unpack_cylinder(const t_primitive_array *p, int i);
t_cone		unpack_cone(const t_primitive_array *p, int i);
t_box		unpack_box(const t_primitive_array *p, int i);
t_capsule	unpack_capsule(const t_primitive_array *p, int i);
t_rect_scratch	unpack_rect(const t_primitive_array *p, int i);
t_pyramid	unpack_pyramid(const t_primitive_array *p, int i);
t_tri_view	unpack_tri(const t_tri_array *t, int i);

#endif
