/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:10:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	hit_plane(const t_plane *p, const t_ray *r, t_hit *h)
{
	float	denom;
	float	t;

	denom = v3_dot(r->d, p->normal);
	if (fabsf(denom) < EPSILON)
		return (0);
	t = v3_dot(v3_sub(p->point, r->o), p->normal) / denom;
	if (t <= EPSILON || t >= h->t)
		return (0);
	h->t = t;
	h->p = ray_at(*r, t);
	h->n = v3_norm(p->normal);
	if (v3_dot(h->n, r->d) > 0.0f)
		h->n = v3_neg(h->n);
	return (1);
}
