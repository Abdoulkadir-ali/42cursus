/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:25:09 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:46:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "material.h"
# include "maths.h"

typedef enum e_obj_type
{
	OBJ_SPHERE = 0,
	OBJ_PLANE = 1,
	OBJ_CYLINDER = 2,
	OBJ_BOX = 3,
	OBJ_CAPSULE = 4,
	OBJ_PYRAMID = 5,
	OBJ_TRIANGLE = 6
}				t_obj_type;

typedef struct s_sphere
{
	t_vec3	center;
	float	radius;
	float	radius2;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3	base;
	t_vec3	axis;
	float	radius;
	float	height;
	float	radius2;
}			t_cylinder;

typedef struct s_box
{
	t_vec3	center;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_vec3	he;
}			t_box;

typedef struct s_capsule
{
	t_vec3	base;
	t_vec3	axis;
	float	radius;
	float	height;
	float	radius2;
}			t_capsule;

typedef struct s_pyramid
{
	t_vec3	base;
	t_vec3	axis;
	float	side;
	float	height;
	t_vec3	apex;
	t_vec3	u;
	t_vec3	v;
}			t_pyramid;

typedef struct s_triangle
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	n;
	float	uv[6];
}			t_triangle;

typedef struct s_object
{
	int			type;
	int			group_id;
	t_vec3		color;
	t_material	mat;
	union
	{
		t_sphere	sph;
		t_plane		pln;
		t_cylinder	cyl;
		t_box		box;
		t_capsule	cap;
		t_pyramid	pyr;
		t_triangle	tri;
	}			u;
}				t_object;

typedef struct s_hit
{
	float				t;
	t_vec3				p;
	t_vec3				n;
	int					obj_index;
	t_vec3				color;
	float				u;
	float				v;
	const t_material	*mat;
}						t_hit;

#endif
