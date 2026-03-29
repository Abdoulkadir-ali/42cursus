/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:50:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"
#include <math.h>

t_vec3	vec3_lerp_clamped(t_vec3 a, t_vec3 b, float t)
{
	if (t <= 0.0f)
		return (a);
	if (t >= 1.0f)
		return (b);
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

t_vec3	quat_nlerp(t_vec3 a, t_vec3 b, float t)
{
	double	len;
	t_vec3	res;

	if (t <= 0.0f)
		return (a);
	if (t >= 1.0f)
		return (b);
	res = vec3_add(a, vec3_scale(vec3_sub(b, a), t));
	len = sqrt(res.x * res.x + res.y * res.y + res.z * res.z + res.w * res.w);
	if (len > EPSILON)
	{
		res.x *= (1.0 / len);
		res.y *= (1.0 / len);
		res.z *= (1.0 / len);
		res.w *= (1.0 / len);
	}
	return (res);
}

static t_vec3	slerp_linear_fallback(t_vec3 a, t_vec3 b, float t)
{
	t_vec3	res;
	double	len;

	res.x = a.x + t * (b.x - a.x);
	res.y = a.y + t * (b.y - a.y);
	res.z = a.z + t * (b.z - a.z);
	res.w = a.w + t * (b.w - a.w);
	len = sqrt(res.x * res.x + res.y * res.y
			+ res.z * res.z + res.w * res.w);
	if (len > 1e-12)
	{
		res.x /= len;
		res.y /= len;
		res.z /= len;
		res.w /= len;
	}
	return (res);
}

t_vec3	quat_slerp(t_vec3 a, t_vec3 b, float t)
{
	double	cos_theta;
	double	theta;
	double	w[2];
	t_vec3	res;

	if (t <= 0.0f)
		return (a);
	if (t >= 1.0f)
		return (b);
	cos_theta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	if (cos_theta < 0.0 && (cos_theta = -cos_theta))
	{
		b = vec3(-b.x, -b.y, -b.z);
		b.w = -b.w;
	}
	if (cos_theta > 0.9995)
		return (slerp_linear_fallback(a, b, t));
	theta = acos(cos_theta);
	if (fabs(sin(theta)) < EPSILON)
		return (quat_nlerp(a, b, t));
	w[0] = sin((1.0 - t) * theta) / sin(theta);
	w[1] = sin(t * theta) / sin(theta);
	res = vec3_add(vec3_scale(a, w[0]), vec3_scale(b, w[1]));
	res.w = a.w * w[0] + b.w * w[1];
	return (res);
}

t_vec3	vec3_step(t_vec3 a, t_vec3 b, float t)
{
	if (t >= 1.0f)
		return (b);
	return (a);
}

t_mat4	quat_to_mat4(t_vec3 q)
{
	t_mat4	m;
	double	v2[3];
	double	xyzw[6];
	double	w_xyz[3];

	m = mat4_identity();
	v2[0] = q.x + q.x;
	v2[1] = q.y + q.y;
	v2[2] = q.z + q.z;
	xyzw[0] = q.x * v2[0];
	xyzw[1] = q.x * v2[1];
	xyzw[2] = q.x * v2[2];
	xyzw[3] = q.y * v2[1];
	xyzw[4] = q.y * v2[2];
	xyzw[5] = q.z * v2[2];
	w_xyz[0] = q.w * v2[0];
	w_xyz[1] = q.w * v2[1];
	w_xyz[2] = q.w * v2[2];
	m.m[0][0] = 1.0 - (xyzw[3] + xyzw[5]);
	m.m[0][1] = xyzw[1] - w_xyz[2];
	m.m[0][2] = xyzw[2] + w_xyz[1];
	m.m[1][0] = xyzw[1] + w_xyz[2];
	m.m[1][1] = 1.0 - (xyzw[0] + xyzw[5]);
	m.m[1][2] = xyzw[4] - w_xyz[0];
	m.m[2][0] = xyzw[2] - w_xyz[1];
	m.m[2][1] = xyzw[4] + w_xyz[0];
	m.m[2][2] = 1.0 - (xyzw[0] + xyzw[3]);
	return (m);
}

t_vec3	anim_interpolate(t_anim_sampler *s, int frame, float t, t_anim_path path)
{
	int		dim;
	int		k1;
	int		k2;
	t_vec3	a;
	t_vec3	b;

	dim = 3;
	if (path == PATH_ROTATION)
		dim = 4;
	k1 = frame;
	k2 = frame;
	if (frame + 1 < s->count)
		k2 = frame + 1;
	a = vec3(s->outputs[k1 * dim], s->outputs[k1 * dim + 1],
			s->outputs[k1 * dim + 2]);
	if (dim == 4)
		a.w = s->outputs[k1 * dim + 3];
	b = vec3(s->outputs[k2 * dim], s->outputs[k2 * dim + 1],
			s->outputs[k2 * dim + 2]);
	if (dim == 4)
		b.w = s->outputs[k2 * dim + 3];
	if (s->method == INTERP_STEP)
		return (vec3_step(a, b, t));
	if (path == PATH_ROTATION)
		return (quat_slerp(a, b, t));
	return (vec3_lerp_clamped(a, b, t));
}
