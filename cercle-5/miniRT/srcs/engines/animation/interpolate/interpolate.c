/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:42:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"
#include <math.h>

t_vec3	vec3_lerp_clamped(t_vec3 a, t_vec3 b, float t)
{
	if (t <= 0.0f) return (a);
	if (t >= 1.0f) return (b);
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

t_vec3	quat_slerp(t_vec3 a, t_vec3 b, float t)
{
	double	cos_theta;
	double	sin_theta;
	double	theta;
	double	w1;
	double	w2;

	if (t <= 0.0f) return (a);
	if (t >= 1.0f) return (b);
	cos_theta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	if (cos_theta < 0.0)
	{
		b = vec3(-b.x, -b.y, -b.z);
		b.w = -b.w;
		cos_theta = -cos_theta;
	}
	if (cos_theta > 0.9995)
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
			res.x /= len; res.y /= len;
			res.z /= len; res.w /= len;
		}
		return (res);
	}
	theta = acos(cos_theta);
	sin_theta = sin(theta);
	w1 = sin((1.0 - t) * theta) / sin_theta;
	w2 = sin(t * theta) / sin_theta;
	t_vec3 res = vec3_add(vec3_scale(a, w1), vec3_scale(b, w2));
	res.w = a.w * w1 + b.w * w2;
	return (res);
}

t_vec3	vec3_step(t_vec3 a, t_vec3 b, float t)
{
	(void)b;
	if (t >= 1.0f) return (b);
	return (a);
}

t_mat4	quat_to_mat4(t_vec3 q)
{
	t_mat4	m;
	double	x2, y2, z2, xx, xy, xz, yy, yz, zz, wx, wy, wz;

	m = mat4_identity();
	x2 = q.x + q.x; y2 = q.y + q.y; z2 = q.z + q.z;
	xx = q.x * x2; xy = q.x * y2; xz = q.x * z2;
	yy = q.y * y2; yz = q.y * z2; zz = q.z * z2;
	wx = q.w * x2; wy = q.w * y2; wz = q.w * z2;
	m.m[0][0] = 1.0 - (yy + zz);
	m.m[0][1] = xy - wz;
	m.m[0][2] = xz + wy;
	m.m[1][0] = xy + wz;
	m.m[1][1] = 1.0 - (xx + zz);
	m.m[1][2] = yz - wx;
	m.m[2][0] = xz - wy;
	m.m[2][1] = yz + wx;
	m.m[2][2] = 1.0 - (xx + yy);
	return (m);
}

t_vec3	anim_interpolate(t_anim_sampler *s, int frame, float t, t_anim_path path)
{
	int		dim;
	int		k1, k2;
	float	*v1, *v2;

	dim = (path == PATH_ROTATION) ? 4 : 3;
	k1 = frame;
	k2 = (frame + 1 < s->count) ? frame + 1 : frame;
	v1 = &s->outputs[k1 * dim];
	v2 = &s->outputs[k2 * dim];

	t_vec3 a = vec3(v1[0], v1[1], v1[2]);
	if (dim == 4) a.w = v1[3];
	t_vec3 b = vec3(v2[0], v2[1], v2[2]);
	if (dim == 4) b.w = v2[3];

	if (s->method == INTERP_STEP)
		return (vec3_step(a, b, t));
	if (path == PATH_ROTATION)
		return (quat_slerp(a, b, t));
	return (vec3_lerp_clamped(a, b, t));
}
