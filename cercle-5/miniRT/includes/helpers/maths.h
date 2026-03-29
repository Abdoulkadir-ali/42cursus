/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:43:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

/* STD lib */
# include "libft.h"
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

/**
 * @brief 3D vector with homogeneous/quaternion w component.
 * sizeof(t_vec3) == 32 (not 24) -- 4 doubles packed.
 * w is used for homogeneous coords and quaternion storage.
 * SoA/AABB code must treat w as 0.0 for direction vectors.
 */
typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec3;

typedef t_vec3	t_vec4;

typedef struct s_mat4
{
	double		m[4][4];
}				t_mat4;

typedef struct s_mat3
{
	double		m[3][3];
}				t_mat3;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	t_vec3		inv_dir;
	int			sign[3];
	int			depth;
	double		weight;
}				t_ray;

typedef struct s_aabb
{
	t_vec3		min;
	t_vec3		max;
}				t_aabb;


typedef struct s_rotator
{
	double		pitch;
	double		yaw;
	double		roll;
}				t_rotator;

typedef struct s_transform
{
	t_vec3		pos;
	t_rotator	rotation;
	t_vec3		scale;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
}				t_transform;

typedef struct s_quadratic
{
	double		a;
	double		b;
	double		c;
}				t_quadratic;

typedef struct s_quadratic_roots
{
	double		t1;
	double		t2;
}				t_quadratic_roots;

typedef struct s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct s_vec3i
{
	int			x;
	int			y;
	int			z;
	int			w;
}				t_vec3i;

t_vec2i			vec2i(int x, int y);
t_vec2i			vec2i_add(t_vec2i a, t_vec2i b);
t_vec2i			vec2i_sub(t_vec2i a, t_vec2i b);
t_vec2i			vec2i_mul(t_vec2i a, t_vec2i b);
t_vec2i			vec2i_scale(t_vec2i a, int s);
int				vec2i_dot(t_vec2i a, t_vec2i b);
int				vec2i_mag_sq(t_vec2i a);
int				vec2i_mag(t_vec2i a);
t_vec2i			vec2i_norm(t_vec2i a);

t_vec3i			vec3i(int x, int y, int z);
t_vec3i			vec3i_add(t_vec3i a, t_vec3i b);
t_vec3i			vec3i_sub(t_vec3i a, t_vec3i b);
t_vec3i			vec3i_mul(t_vec3i a, t_vec3i b);
t_vec3i			vec3i_scale(t_vec3i a, int s);
int				vec3i_dot(t_vec3i a, t_vec3i b);
t_vec3i			vec3i_cross(t_vec3i a, t_vec3i b);
int				vec3i_mag_sq(t_vec3i a);
int				vec3i_mag(t_vec3i a);
t_vec3i			vec3i_norm(t_vec3i a);

/* vec2 */
t_vec2			vec2(double x, double y);
t_vec2			vec2_pt(double x, double y);
t_vec2			vec2_add(t_vec2 a, t_vec2 b);
t_vec2			vec2_sub(t_vec2 a, t_vec2 b);
t_vec2			vec2_mul(t_vec2 a, t_vec2 b);
t_vec2			vec2_scale(t_vec2 a, double s);
double			vec2_dot(t_vec2 a, t_vec2 b);
double			vec2_mag_sq(t_vec2 a);
double			vec2_mag(t_vec2 a);
t_vec2			vec2_norm(t_vec2 a);

/* vec3 — declarations */
t_vec3			vec3(double x, double y, double z);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_mul(t_vec3 a, t_vec3 b);
t_vec3			vec3_scale(t_vec3 a, double s);
double			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
t_vec3			vec3_triple_product(t_vec3 a, t_vec3 b, t_vec3 c);
double			vec3_mag_sq(t_vec3 a);
double			vec3_mag(t_vec3 a);
t_vec3			vec3_pt(double x, double y, double z);
t_vec3			vec3_norm(t_vec3 a);
t_vec3			vec3_lerp(t_vec3 a, t_vec3 b, double t);
t_vec3			vec3_min(t_vec3 a, t_vec3 b);
t_vec3			vec3_max(t_vec3 a, t_vec3 b);
bool			vec3_compare(t_vec3 a, t_vec3 b);
void			vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent,
					t_vec3 *bitangent);
t_vec3			get_camera_forward(double pitch, double yaw);
t_vec3			rotate_vector(t_vec3 v, double pitch, double yaw);

/* mat4 */
t_mat4			mat4_mul(t_mat4 a, t_mat4 b);
t_mat4			mat4_identity(void);
t_vec3			mat4_mul_vec3(t_mat4 m, t_vec3 v);
t_mat4			mat4_scale_inplace(t_mat4 m, double s);
t_mat4			mat4_add(t_mat4 a, t_mat4 b);
t_mat4			mat4_translation(t_vec3 v);
t_mat4			mat4_scaling(t_vec3 v);
t_mat4			mat4_rotation(t_rotator r);
t_mat4			mat4_transform(t_transform t);
t_mat4			mat4_inverse_transform(t_transform t);
t_vec3			mat4_mul_pos(t_mat4 m, t_vec3 v);

/* mat3 */
t_vec3			mat3_mul_vec3(t_mat3 m, t_vec3 v);
t_mat3			mat3_mul(t_mat3 a, t_mat3 b);
t_mat3			mat3_transpose(t_mat3 m);
bool			mat3_inv(t_mat3 m, t_mat3 *out);
t_mat3			mat3_diag(t_vec3 v);

t_vec3			vec3_reflect(t_vec3 I, t_vec3 N);
t_vec3			vec3_refract(t_vec3 I, t_vec3 N, double ior);

/* Roots */
bool			solve_quadratic(t_quadratic q, t_quadratic_roots *roots);
double			clamp_d(double v, double lo, double hi);
int				clamp_i(int v, int lo, int hi);
t_vec2			clamp_vec2(t_vec2 v, t_vec2 min, t_vec2 max);
t_vec2			clamp_vec2d(t_vec2 v, double lo, double hi);
t_vec3			clamp_vec3(t_vec3 v, t_vec3 min, t_vec3 max);
t_vec3			clamp_vec3d(t_vec3 v, double lo, double hi);

/* AABB */
t_aabb			aabb_create_empty(void);
void			aabb_expand_point(t_aabb *aabb, t_vec3 p);
t_aabb			aabb_union(const t_aabb *a, const t_aabb *b);
bool			aabb_overlap(const t_aabb *a, const t_aabb *b);
void			aabb_expand_eps(t_aabb *aabb, double eps);
double			aabb_surface_area(const t_aabb *aabb);

/* --- NUMERIC CONSTANTS (see REPORT.md: BUG-U01 re EPSILON usage) --- */
# define EPSILON 1e-6
# define EPSILON_MUL 10.0
# define MAG_EPSILON 1e-6
# define SCALE_EPSILON 1e-6
# define MAX_VALUE 1e30
# define SAFE_RCP_MIN 1e-20
# define HALF_SCALE 0.5f
# define BITS_PER_BYTE 8

#endif
