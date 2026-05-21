/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:10:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef EPSILON
#  define EPSILON 1e-4f
# endif
# ifndef T_MAX
#  define T_MAX 1e30f
# endif

/* ---- Vector Types ---- */
typedef struct s_vec2
{
	float	x;
	float	y;
}			t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef union u_vec4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float	v[4];
}			t_vec4;

typedef struct s_vec2i
{
	int	x;
	int	y;
}		t_vec2i;

typedef struct s_vec3i
{
	int	x;
	int	y;
	int	z;
}		t_vec3i;

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

typedef struct s_ray
{
	t_vec3	o;
	t_vec3	d;
}			t_ray;

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

/* Column-major 4x4 matrix (GLSL/glTF convention).
 * Defined as a fixed-size array so it can be passed to existing
 * raw `float *` matrix helpers without `.m` indirection. */
typedef float	t_mat4[16];

/* ---- Inline scalar helpers ---- */
static inline float	ft_clampf(float v, float lo, float hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static inline int	ft_clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

/* ---- Inline Vec2 ops ---- */
static inline t_vec2	v2(float x, float y)
{
	return ((t_vec2){x, y});
}

static inline t_vec2	v2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

static inline t_vec2	v2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

static inline t_vec2	v2_mul(t_vec2 a, float s)
{
	return ((t_vec2){a.x * s, a.y * s});
}

static inline float	v2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

static inline float	v2_len(t_vec2 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

static inline t_vec2	v2_norm(t_vec2 a)
{
	float	len;

	len = v2_len(a);
	if (len > 0.0f)
		return (v2_mul(a, 1.0f / len));
	return ((t_vec2){0.0f, 0.0f});
}

/* ---- Inline Vec3 ops ---- */
static inline t_vec3	v3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

static inline t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

static inline t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

static inline t_vec3	v3_mul(t_vec3 a, float s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s});
}

static inline t_vec3	ray_at(t_ray r, float t)
{
	return ((t_vec3){r.o.x + r.d.x * t, r.o.y + r.d.y * t, r.o.z + r.d.z * t});
}

static inline t_vec3	v3_neg(t_vec3 a)
{
	return ((t_vec3){-a.x, -a.y, -a.z});
}

static inline t_vec3	v3_hmul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

static inline float	v3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

static inline float	v3_len(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

static inline t_vec3	v3_norm(t_vec3 a)
{
	float	len;

	len = v3_len(a);
	if (len > 0.0f)
		return (v3_mul(a, 1.0f / len));
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

/* ---- Vec3 / colour utilities ---- */
void			basis_from_axis(t_vec3 axis, t_vec3 *u, t_vec3 *v);
float			halton(int i, int b);
int				ft_argb(float r, float g, float b);
unsigned int	rgb_pack(t_vec3 c);

/* ---- AABB Utilities ---- */
void			aabb_reset(t_aabb *b);
void			aabb_expand(t_aabb *b, t_vec3 p);
void			aabb_union(t_aabb *b, const t_aabb *o);
float			aabb_area(const t_aabb *b);
int				aabb_hit(const t_aabb *b, const t_ray *r,
					const t_vec3 inv_d, float t_max);

#endif
