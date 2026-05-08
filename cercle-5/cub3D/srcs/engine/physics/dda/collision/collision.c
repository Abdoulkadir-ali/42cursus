/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:45:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:54:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static	int	calc_hit_side(t_dda *d, t_vec2 min)
{
	float	hx;
	float	hy;

	hx = (min.x - d->origin.x) / d->ray.x;
	hy = (min.y - d->origin.y) / d->ray.y;
	if (hx > hy)
		return (1);
	return (0);
}

bool	push_aabb_hit(t_dda *d, t_map *map, float *dist, int *side)
{
	t_push_wall	*pw;
	t_vec2		min;
	t_vec2		t;

	pw = get_push_wall(d, map);
	if (!pw || !pw->active)
		return (false);
	min = get_pw_min(pw);
	if (!calc_aabb_t(d, min, &t))
		return (false);
	*dist = t.x;
	*side = calc_hit_side(d, min);
	return (true);
}
