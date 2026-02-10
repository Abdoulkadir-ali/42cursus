/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:10:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include <stdbool.h>
# include <stddef.h>

#define MAX_VALUE 1e30

typedef struct s_vec2
{
	double				x;
	double				y;
}						t_vec2;

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
	double				w;
}						t_vec3;

typedef struct s_mat4
{
	double				m[4][4];
}						t_mat4;

typedef struct s_aabb
{
	t_vec3				min;
	t_vec3				max;
}						t_aabb;

typedef struct s_rotator
{
	double				pitch;
	double				yaw;
	double				roll;
}						t_rotator;

typedef struct s_transform
{
	t_vec3				pos;
	t_rotator			rotation;
	t_vec3				scale;
	t_vec3				forward;
	t_vec3				right;
	t_vec3				up;
}						t_transform;

/* vec2 (Inline) */
static inline t_vec2	vec2(double x, double y)
{
	return ((t_vec2){x, y});
}
static inline t_vec2	vec2_pt(double x, double y)
{
	return ((t_vec2){x, y});
}
static inline t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}
static inline t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}
static inline t_vec2	vec2_mul(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x * b.x, a.y * b.y});
}
static inline t_vec2	vec2_scale(t_vec2 a, double s)
{
	return ((t_vec2){a.x * s, a.y * s});
}
static inline double	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}
static inline double	vec2_mag_sq(t_vec2 a)
{
	return (vec2_dot(a, a));
}
static inline double	vec2_mag(t_vec2 a)
{
	return (sqrt(vec2_mag_sq(a)));
}
static inline t_vec2	vec2_norm(t_vec2 a)
{
	double	mag;

	mag = vec2_mag(a);
	return (mag == 0 ? (t_vec2){0, 0} : vec2_scale(a, 1.0 / mag));
}

/* vec3 (Inline) */
static inline t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 0.0});
}

static inline t_vec3	vec3_pt(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 1.0});
}
static inline t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}
static inline t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}
static inline t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w});
}
static inline t_vec3	vec3_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s, a.w * s});
}
static inline double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
static inline t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x, 0.0});
}
static inline double	vec3_mag_sq(t_vec3 a)
{
	return (vec3_dot(a, a));
}
static inline double	vec3_mag(t_vec3 a)
{
	return (sqrt(vec3_mag_sq(a)));
}
static inline t_vec3	vec3_norm(t_vec3 a)
{
	double	mag;

	mag = vec3_mag(a);
	return (mag == 0 ? (t_vec3){0, 0, 0, 0} : vec3_scale(a, 1.0 / mag));
}
static inline t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

static inline bool	vec3_compare(t_vec3 a, t_vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

static inline t_vec3	get_camera_forward(double pitch, double yaw)
{
	return (vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw)));
}

static inline t_vec3	rotate_vector(t_vec3 v, double pitch, double yaw)
{
	double	y1;
	double	z1;
	t_vec3	v1;
	double	x2;
	double	y2;

	y1 = v.y * cos(pitch) - v.z * sin(pitch);
	z1 = v.y * sin(pitch) + v.z * cos(pitch);
	v1 = vec3(v.x, y1, z1);
	x2 = v1.x * cos(yaw) - v1.y * sin(yaw);
	y2 = v1.x * sin(yaw) + v1.y * cos(yaw);
	return (vec3(x2, y2, v1.z));
}

static inline t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			res.m[i][j] = 0;
			for (k = 0; k < 4; k++)
				res.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (res);
}

static inline t_mat4	mat4_identity(void)
{
	t_mat4	res;
	int		i;
	int		j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			res.m[i][j] = (i == j);
	return (res);
}

static inline t_vec3	mat4_mul_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3	res;

	res.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w
		* m.m[3][0];
	res.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w
		* m.m[3][1];
	res.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w
		* m.m[3][2];
	res.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w
		* m.m[3][3];
	return (res);
}

static inline t_mat4	mat4_id(void)
{
	t_mat4	m;

	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			m.m[i][j] = (i == j);
	return (m);
}

static inline t_mat4	mat4_scale_inplace(t_mat4 m, double s)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m.m[i][j] *= s;
	return (m);
}

static inline t_mat4	mat4_add(t_mat4 a, t_mat4 b)
{
	t_mat4	res;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res.m[i][j] = a.m[i][j] + b.m[i][j];
	return (res);
}

static inline t_mat4	mat4_translation(t_vec3 v)
{
	t_mat4	m = mat4_identity();
	m.m[3][0] = v.x;
	m.m[3][1] = v.y;
	m.m[3][2] = v.z;
	return (m);
}

static inline t_mat4	mat4_scaling(t_vec3 v)
{
	t_mat4	m = mat4_identity();
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	return (m);
}

static inline t_mat4	mat4_rotation(t_rotator r)
{
	t_mat4 m = mat4_identity();
	double p = r.pitch * M_PI / 180.0;
	double y = r.yaw * M_PI / 180.0;
	double rl = r.roll * M_PI / 180.0;
	double cp = cos(p), sp = sin(p);
	double cy = cos(y), sy = sin(y);
	double cr = cos(rl), sr = sin(rl);

	m.m[0][0] = cy * cr;
	m.m[0][1] = cy * sr;
	m.m[0][2] = -sy;
	m.m[1][0] = sp * sy * cr - cp * sr;
	m.m[1][1] = sp * sy * sr + cp * cr;
	m.m[1][2] = sp * cy;
	m.m[2][0] = cp * sy * cr + sp * sr;
	m.m[2][1] = cp * sy * sr - sp * cr;
	m.m[2][2] = cp * cy;
	return (m);
}

static inline t_mat4	mat4_transform(t_transform t)
{
	t_mat4 m;
	m = mat4_mul(mat4_scaling(t.scale), mat4_rotation(t.rotation));
	m = mat4_mul(m, mat4_translation(t.pos));
	return (m);
}

static inline t_vec3	mat4_mul_pos(t_mat4 m, t_vec3 v)
{
	t_vec3 res;
	double w;
	res.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	res.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	res.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	res.w = 1.0;
	w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	if (w != 0 && w != 1.0)
	{
		res.x /= w; res.y /= w; res.z /= w;
	}
	return (res);
}

/* Roots */
bool					solve_quadratic(double a, double b, double c,
							double *t1, double *t2);

#endif
