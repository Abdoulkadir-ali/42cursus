/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackhole.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:09:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static int	bend_one(t_ray *r, const t_blackhole *bh)
{
	t_vec3	oc;
	float	tca;
	float	d2;
	float	b;
	t_vec3	closest;
	t_vec3	n;
	float	alpha;
	float	rs;

	rs = bh->rs;
	oc = v3_sub(bh->pos, r->o);
	tca = v3_dot(oc, r->d);
	if (tca <= 0.0f)
		return (0);
	d2 = v3_dot(oc, oc) - tca * tca;
	if (d2 < 0.0f)
		d2 = 0.0f;
	b = sqrtf(d2);
	if (b < rs)
		return (1);
	if (b > rs * 30.0f)
		return (0);
	closest = v3_add(r->o, v3_mul(r->d, tca));
	n = v3_sub(bh->pos, closest);
	if (v3_dot(n, n) < 1e-8f)
		return (1);
	n = v3_norm(n);
	alpha = (2.0f * rs / b) * bh->lens_strength;
	if (alpha > 1.2f)
		alpha = 1.2f;
	r->d = v3_norm(v3_add(v3_mul(r->d, cosf(alpha)),
				v3_mul(n, sinf(alpha))));
	return (0);
}

int	ray_bend_blackholes(const t_scene *s, t_ray *r)
{
	size_t	i;

	i = 0;
	while (i < s->n_bhs)
	{
		if (bend_one(r, &s->bhs[i]))
			return (1);
		i++;
	}
	return (0);
}