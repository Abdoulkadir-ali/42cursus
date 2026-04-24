/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:35:56 by abdoali          ###   ########.fr       */
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
bool								aabb_intersect(const t_ray *ray,
										const t_aabb *box, double *t);
static inline __attribute__((always_inline))
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
			double *tmax)
{
	double	t1;
	double	t2;
	double	mn;
	double	mx;

	t1 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	mn = t1 < t2 ? t1 : t2;
	mx = t1 > t2 ? t1 : t2;
	t1 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	mn = (t1 < t2 ? t1 : t2) > mn ? (t1 < t2 ? t1 : t2) : mn;
	mx = (t1 > t2 ? t1 : t2) < mx ? (t1 > t2 ? t1 : t2) : mx;
	t1 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	mn = (t1 < t2 ? t1 : t2) > mn ? (t1 < t2 ? t1 : t2) : mn;
	mx = (t1 > t2 ? t1 : t2) < mx ? (t1 > t2 ? t1 : t2) : mx;
	*tmin = mn;
	*tmax = mx;
	return (mx >= 0.0 && mx >= mn);
}

static inline __attribute__((always_inline))
bool	aabb_intersect_fast_f(const float min[3], const float max[3],
			const t_ray *ray, float *tmin, float *tmax)
{
	float	t[2];
	float	mn;
	float	mx;

	t[0] = (min[0] - (float)ray->origin.x) * (float)ray->inv_dir.x;
	t[1] = (max[0] - (float)ray->origin.x) * (float)ray->inv_dir.x;
	mn = t[0] < t[1] ? t[0] : t[1];
	mx = t[0] > t[1] ? t[0] : t[1];
	t[0] = (min[1] - (float)ray->origin.y) * (float)ray->inv_dir.y;
	t[1] = (max[1] - (float)ray->origin.y) * (float)ray->inv_dir.y;
	mn = (t[0] < t[1] ? t[0] : t[1]) > mn ? (t[0] < t[1] ? t[0] : t[1]) : mn;
	mx = (t[0] > t[1] ? t[0] : t[1]) < mx ? (t[0] > t[1] ? t[0] : t[1]) : mx;
	t[0] = (min[2] - (float)ray->origin.z) * (float)ray->inv_dir.z;
	t[1] = (max[2] - (float)ray->origin.z) * (float)ray->inv_dir.z;
	mn = (t[0] < t[1] ? t[0] : t[1]) > mn ? (t[0] < t[1] ? t[0] : t[1]) : mn;
	mx = (t[0] > t[1] ? t[0] : t[1]) < mx ? (t[0] > t[1] ? t[0] : t[1]) : mx;
	*tmin = mn;
	*tmax = mx;
	return (mx >= 0.0f && mx >= mn);
}
t_aabb								aabb_init(void);

static inline __attribute__((always_inline))
t_aabb	aabb_create_empty(void)
{
	t_aabb	b;

	b.min.x = MAX_VALUE; b.min.y = MAX_VALUE; b.min.z = MAX_VALUE; b.min.w = 0;
	b.max.x = -MAX_VALUE; b.max.y = -MAX_VALUE; b.max.z = -MAX_VALUE; b.max.w = 0;
	return (b);
}

static inline __attribute__((always_inline))
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	r;

	r.min.x = a->min.x < b->min.x ? a->min.x : b->min.x;
	r.min.y = a->min.y < b->min.y ? a->min.y : b->min.y;
	r.min.z = a->min.z < b->min.z ? a->min.z : b->min.z;
	r.min.w = 0;
	r.max.x = a->max.x > b->max.x ? a->max.x : b->max.x;
	r.max.y = a->max.y > b->max.y ? a->max.y : b->max.y;
	r.max.z = a->max.z > b->max.z ? a->max.z : b->max.z;
	r.max.w = 0;
	return (r);
}

static inline __attribute__((always_inline))
void	aabb_expand_point(t_aabb *bbox, t_vec3 p)
{
	if (p.x < bbox->min.x) bbox->min.x = p.x;
	if (p.y < bbox->min.y) bbox->min.y = p.y;
	if (p.z < bbox->min.z) bbox->min.z = p.z;
	if (p.x > bbox->max.x) bbox->max.x = p.x;
	if (p.y > bbox->max.y) bbox->max.y = p.y;
	if (p.z > bbox->max.z) bbox->max.z = p.z;
}

t_vec2i								vec2i(int x, int y);
t_vec2i								vec2i_add(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_sub(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_mul(t_vec2i a, t_vec2i b);
t_vec2i								vec2i_scale(t_vec2i a, int s);
int									vec2i_dot(t_vec2i a, t_vec2i b);
int									vec2i_mag_sq(t_vec2i a);
int									vec2i_mag(t_vec2i a);
t_vec2i								vec2i_norm(t_vec2i a);

t_vec2s								vec2s(size_t x, size_t y);
t_vec2s								vec2s_add(t_vec2s a, t_vec2s b);
t_vec2s								vec2s_sub(t_vec2s a, t_vec2s b);



t_vec3i								vec3i(int x, int y, int z);
t_vec3i								vec3i_add(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_sub(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_mul(t_vec3i a, t_vec3i b);
t_vec3i								vec3i_scale(t_vec3i a, int s);

t_vec3s								vec3s(size_t x, size_t y, size_t z);
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

/* vec3 — hot constructors inlined */
static inline __attribute__((always_inline))
t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 0.0});
}

static inline __attribute__((always_inline))
t_vec3	vec3_pt(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 1.0});
}
t_vec3								vec3_lerp(t_vec3 a, t_vec3 b, double t);
t_vec3								vec3_min(t_vec3 a, t_vec3 b);
t_vec3								vec3_max(t_vec3 a, t_vec3 b);
bool								vec3_compare(t_vec3 a, t_vec3 b);
t_vec3								get_camera_forward(double pitch,
										double yaw);
t_vec3								rotate_vector(t_vec3 v, double pitch,
										double yaw);

static inline __attribute__((always_inline))
t_vec3	vec3_norm(t_vec3 a)
{
	double	mag_sq;
	double	inv;

	mag_sq = a.x * a.x + a.y * a.y + a.z * a.z;
	if (mag_sq < 1e-24)
		return ((t_vec3){0, 0, 0, 0});
	inv = 1.0 / __builtin_sqrt(mag_sq);
	return ((t_vec3){a.x * inv, a.y * inv, a.z * inv, 0.0});
}

static inline __attribute__((always_inline))
void	vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent,
	t_vec3 *bitangent)
{
	t_vec3	up;

	if (normal.y > 0.9 || normal.y < -0.9)
		up = (t_vec3){1, 0, 0, 0};
	else
		up = (t_vec3){0, 1, 0, 0};
	*bitangent = vec3_norm((t_vec3){
		normal.y * up.z - normal.z * up.y,
		normal.z * up.x - normal.x * up.z,
		normal.x * up.y - normal.y * up.x, 0});
	*tangent = vec3_norm((t_vec3){
		bitangent->y * normal.z - bitangent->z * normal.y,
		bitangent->z * normal.x - bitangent->x * normal.z,
		bitangent->x * normal.y - bitangent->y * normal.x, 0});
}

/*
** Hot-path vec3 ops: static inline so each TU gets the body and the
** per-TU optimiser can inline/vectorise them without waiting for LTO.
** The matching bodies in vec3.c / vec3_ops.c are guarded by this macro.
*/
# define VEC3_HOT_INLINE 1

/* Force inline in profile build (-O1); compiler handles it at -O3 */
# ifdef PROFILE_BUILD
#  define PROF_HOT __attribute__((always_inline))
# else
#  define PROF_HOT
# endif

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

/* Float vector helpers */
static inline t_vec3f	vec3f_add(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

static inline t_vec3f	vec3f_muls(t_vec3f a, float s)
{
	return ((t_vec3f){a.x * s, a.y * s, a.z * s, a.w * s});
}

#endif
