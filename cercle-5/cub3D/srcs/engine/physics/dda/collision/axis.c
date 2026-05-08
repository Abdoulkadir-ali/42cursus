/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

bool	calc_axis(float ray, float origin, t_vec2 bounds, t_vec2 *t)
{
	float	t1;
	float	t2;

	if (fabsf(ray) < MIN)
		return (origin >= bounds.x && origin <= bounds.y);
	t1 = (bounds.x - origin) / ray;
	t2 = (bounds.y - origin) / ray;
	t->x = fmaxf(t->x, fminf(t1, t2));
	t->y = fminf(t->y, fmaxf(t1, t2));
	return (true);
}

bool	calc_aabb_t(t_dda *d, t_vec2 min, t_vec2 *t)
{
	*t = (t_vec2){-NEG_INF, NEG_INF};
	if (!calc_axis(d->ray.x, d->origin.x, (t_vec2){min.x, min.x + 1.0f}, t))
		return (false);
	if (!calc_axis(d->ray.y, d->origin.y, (t_vec2){min.y, min.y + 1.0f}, t))
		return (false);
	if (t->y < t->x || t->y <= 0.0f)
		return (false);
	if (t->x < 0.0f)
		t->x = t->y;
	return (true);
}
