/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 17:09:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}			t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vec3;

typedef struct s_mat4
{
	double	m[4][4];
}			t_mat4;

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

/* vec2 (Inline) */
static inline t_vec2 vec2(double x, double y) { return ((t_vec2){x, y}); }
static inline t_vec2 vec2_pt(double x, double y) { return ((t_vec2){x, y}); }
static inline t_vec2 vec2_add(t_vec2 a, t_vec2 b) { return ((t_vec2){a.x + b.x, a.y + b.y}); }
static inline t_vec2 vec2_sub(t_vec2 a, t_vec2 b) { return ((t_vec2){a.x - b.x, a.y - b.y}); }
static inline t_vec2 vec2_mul(t_vec2 a, t_vec2 b) { return ((t_vec2){a.x * b.x, a.y * b.y}); }
static inline t_vec2 vec2_scale(t_vec2 a, double s) { return ((t_vec2){a.x * s, a.y * s}); }
static inline double vec2_dot(t_vec2 a, t_vec2 b) { return (a.x * b.x + a.y * b.y); }
static inline double vec2_mag_sq(t_vec2 a) { return (vec2_dot(a, a)); }
static inline double vec2_mag(t_vec2 a) { return (sqrt(vec2_mag_sq(a))); }
static inline t_vec2 vec2_norm(t_vec2 a) {
	double mag = vec2_mag(a);
	return (mag == 0 ? (t_vec2){0, 0} : vec2_scale(a, 1.0 / mag));
}

/* vec3 (Inline) */
static inline t_vec3 vec3(double x, double y, double z) { return ((t_vec3){x, y, z, 0.0}); }
static inline t_vec3 vec3_pt(double x, double y, double z) { return ((t_vec3){x, y, z, 1.0}); }
static inline t_vec3 vec3_add(t_vec3 a, t_vec3 b) { return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}); }
static inline t_vec3 vec3_sub(t_vec3 a, t_vec3 b) { return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}); }
static inline t_vec3 vec3_mul(t_vec3 a, t_vec3 b) { return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}); }
static inline t_vec3 vec3_scale(t_vec3 a, double s) { return ((t_vec3){a.x * s, a.y * s, a.z * s, a.w * s}); }
static inline double vec3_dot(t_vec3 a, t_vec3 b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
static inline t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
	return ((t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0.0
	});
}
static inline double vec3_mag_sq(t_vec3 a) { return (vec3_dot(a, a)); }
static inline double vec3_mag(t_vec3 a) { return (sqrt(vec3_mag_sq(a))); }
static inline t_vec3 vec3_norm(t_vec3 a) {
	double mag = vec3_mag(a);
	return (mag == 0 ? (t_vec3){0, 0, 0, 0} : vec3_scale(a, 1.0 / mag));
}
static inline t_vec3 vec3_lerp(t_vec3 a, t_vec3 b, double t) {
	return vec3_add(a, vec3_scale(vec3_sub(b, a), t));
}

#endif
