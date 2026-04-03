/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "types.h"
# include <float.h>
# include <math.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif
# ifndef EPSILON
#  define EPSILON 1e-6
# endif
# ifndef MAX_VALUE
#  define MAX_VALUE DBL_MAX
# endif
# ifndef MIN_VALUE
#  define MIN_VALUE -DBL_MAX
# endif


/* AABB Utilities (srcs/engines/raytracing/bvh/bound/) */
t_aabb								aabb_union(const t_aabb *a, const t_aabb *b);
bool								aabb_intersect(const t_ray *ray,
										const t_aabb *box, double *t);
bool								aabb_intersect_fast(const t_aabb *box,
										const t_ray *ray, double *tmin,
										double *tmax);
t_aabb								aabb_init(void);
void								aabb_expand_point(t_aabb *bbox, t_vec3 p);
t_aabb								aabb_create_empty(void);

t_vec2i								vec2i(int x, int y);
t_vec2i								vec2i_add(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_sub(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_mul(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_scale(t_vec2i a, int s);
int									vec2i_dot(t_vec2i a, t_vec2i b);
int									vec2i_mag_sq(t_vec2i a);
int									vec2i_mag(t_vec2i a);
t_vec2i								vec2i_norm(t_vec2i a);



t_vec3i								vec3i(int x, int y, int z);
t_vec3i								vec3i_add(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_sub(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_mul(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_scale(t_vec3i a, int s);
int									vec3i_dot(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_cross(t_vec3i a, t_vec3i b);
int									vec3i_mag_sq(t_vec3i a);
int									vec3i_mag(t_vec3i a);
t_vec3i								vec3i_norm(t_vec3i a);

/* vec2 */
t_vec2								vec2(double x, double y);
t_vec2								vec2_pt(double x, double y);
t_vec2								vec2_add(t_vec2 a, t_vec2 b);
t_vec2								vec2_sub(t_vec2 a, t_vec2 b);
t_vec2								vec2_mul(t_vec2 a, t_vec2 b);
t_vec2								vec2_scale(t_vec2 a, double s);
double								vec2_dot(t_vec2 a, t_vec2 b);
double								vec2_mag_sq(t_vec2 a);
double								vec2_mag(t_vec2 a);
t_vec2								vec2_norm(t_vec2 a);

/* vec3 — declarations */
t_vec3								vec3(double x, double y, double z);
t_vec3								vec3_pt(double x, double y, double z);
t_vec3								vec3_norm(t_vec3 a);
t_vec3								vec3_lerp(t_vec3 a, t_vec3 b, double t);
t_vec3								vec3_min(t_vec3 a, t_vec3 b);
t_vec3								vec3_max(t_vec3 a, t_vec3 b);
bool								vec3_compare(t_vec3 a, t_vec3 b);
void								vec3_orthonormal_basis(t_vec3 normal,
										t_vec3 *tangent, t_vec3 *bitangent);
t_vec3								get_camera_forward(double pitch,
										double yaw);
t_vec3								rotate_vector(t_vec3 v, double pitch,
										double yaw);

/*
** Hot-path vec3 ops: static inline so each TU gets the body and the
** per-TU optimiser can inline/vectorise them without waiting for LTO.
** The matching bodies in vec3.c / vec3_ops.c are guarded by this macro.
*/
# define VEC3_HOT_INLINE 1

static inline t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z, 0.0});
}

static inline t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z, 0.0});
}

static inline t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, 0.0});
}

static inline t_vec3	vec3_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s, 0.0});
}

static inline double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x, 0.0});
}

static inline double	vec3_mag_sq(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

static inline double	vec3_mag(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/* mat4 */
t_mat4								mat4_mul(t_mat4 a, t_mat4 b);
t_mat4								mat4_identity(void);
t_vec3								mat4_mul_vec3(t_mat4 m, t_vec3 v);
t_mat4								mat4_scale_inplace(t_mat4 m, double s);
t_mat4								mat4_add(t_mat4 a, t_mat4 b);
t_mat4								mat4_translation(t_vec3 v);
t_mat4								mat4_scaling(t_vec3 v);
t_mat4								mat4_rotation(t_rotator r);
t_mat4								mat4_transform(t_transform t);
t_mat4								mat4_inverse_transform(t_transform t);
t_vec3								mat4_mul_pos(t_mat4 m, t_vec3 v);
t_vec3								mat4_mul_dir(t_mat4 m, t_vec3 v);

t_vec3								vec3_reflect(t_vec3 I, t_vec3 N);
t_vec3								vec3_refract(t_vec3 I, t_vec3 N,
										double ior);

/* Roots */
bool								solve_quadratic(t_quadratic q,
										t_quadratic_roots *roots);

double								aabb_surface_area(t_aabb bbox);

/* Utils */
double								clamp_d(double v, double lo, double hi);
double								lerp_d(double a, double b, double t);
double								normalize_angle(double angle);

#endif
