/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	resolve_pair(t_app *app, t_body *a, t_body *b)
{
	t_vec3	d;
	float	dist2;
	float	r;
	float	dist;
	float	pen;
	t_vec3	n;
	t_vec3	rv;
	float	vn;
	float	e;
	float	j;
	float	w_total;
	float	heat_e;
	float	spec_heat;
	t_vec3	v0;
	float	jt;
	float	mu;

	d = v3_sub(b->pos, a->pos);
	dist2 = v3_dot(d, d);
	r = a->radius_cache + b->radius_cache;
	if (dist2 >= r * r || dist2 < 1e-10f)
		return ;
	dist = sqrtf(dist2);
	pen = r - dist;
	n = v3_mul(d, 1.0f / dist);
	w_total = a->inv_mass + b->inv_mass;
	if (w_total <= 0.0f)
		return ;
	a->pos = v3_sub(a->pos, v3_mul(n, pen * (a->inv_mass / w_total)));
	b->pos = v3_add(b->pos, v3_mul(n, pen * (b->inv_mass / w_total)));
	rv = v3_sub(b->vel, a->vel);
	vn = v3_dot(rv, n);
	if (vn > 0.0f)
		return ;
	e = 0.5f * (a->restitution + b->restitution);
	j = -(1.0f + e) * vn / w_total;
	a->vel = v3_sub(a->vel, v3_mul(n, j * a->inv_mass));
	b->vel = v3_add(b->vel, v3_mul(n, j * b->inv_mass));
	a->sleep_frames = 0;
	b->sleep_frames = 0;
	v0 = v3_sub(rv, v3_mul(n, vn));
	if (v3_dot(v0, v0) > 1e-8f)
	{
		v0 = v3_norm(v0);
		mu = app->set.physics.friction;
		jt = -v3_dot(rv, v0) / w_total;
		if (jt > mu * j)
			jt = mu * j;
		if (jt < -mu * j)
			jt = -mu * j;
		a->vel = v3_sub(a->vel, v3_mul(v0, jt * a->inv_mass));
		b->vel = v3_add(b->vel, v3_mul(v0, jt * b->inv_mass));
	}
	if (app->set.rt.collision_heat)
	{
		heat_e = 0.5f * (1.0f - e * e) * (vn * vn) / w_total;
		spec_heat = 0.05f;
		if (a->inv_mass > 0.0f)
			a->temperature += (heat_e * 0.5f) * a->inv_mass / spec_heat;
		if (b->inv_mass > 0.0f)
			b->temperature += (heat_e * 0.5f) * b->inv_mass / spec_heat;
	}
}
