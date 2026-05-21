/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:16:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

static t_vec4	q_norm(t_vec4 q)
{
	float	n;

	n = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if (n < 1e-9f)
	{
		q.x = 0;
		q.y = 0;
		q.z = 0;
		q.w = 1;
		return (q);
	}
	q.x /= n;
	q.y /= n;
	q.z /= n;
	q.w /= n;
	return (q);
}

static t_vec4	q_lerp(t_vec4 a, t_vec4 b, float t)
{
	t_vec4	o;

	o.x = a.x + t * (b.x - a.x);
	o.y = a.y + t * (b.y - a.y);
	o.z = a.z + t * (b.z - a.z);
	o.w = a.w + t * (b.w - a.w);
	return (q_norm(o));
}

t_vec4	skel_q_slerp(t_vec4 a, t_vec4 b, float t)
{
	float	d;
	float	s0;
	float	s1;
	float	theta;
	t_vec4	o;

	d = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	if (d < 0.0f)
	{
		b.x = -b.x;
		b.y = -b.y;
		b.z = -b.z;
		b.w = -b.w;
		d = -d;
	}
	if (d > 0.9995f)
		return (q_lerp(a, b, t));
	theta = acosf(d);
	s0 = sinf((1.0f - t) * theta) / sinf(theta);
	s1 = sinf(t * theta) / sinf(theta);
	o.x = s0 * a.x + s1 * b.x;
	o.y = s0 * a.y + s1 * b.y;
	o.z = s0 * a.z + s1 * b.z;
	o.w = s0 * a.w + s1 * b.w;
	return (o);
}
