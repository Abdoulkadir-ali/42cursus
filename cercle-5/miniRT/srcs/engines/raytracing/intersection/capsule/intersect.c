/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 18:09:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	set_final_hit(t_capsule *cap, t_hit *hit, t_cap_calc *c,
				const t_ray *ray)
{
	hit->t = c->best;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, c->best));
	update_capsule_hit(cap, hit, c, ray);
}

static void	get_best_hit(t_cap_calc *c)
{
	int	i;

	c->best = 1e30;
	c->type = init_index(0, true);
	i = 0;
	while (i < 3)
	{
		if (c->hit[i] && c->t[i] < c->best)
		{
			c->best = c->t[i];
			c->type = init_index(i, false);
		}
		i++;
	}
}

bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit)
{
	t_cap_calc	c;

	c.p[0] = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.p[1] = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.hit[0] = cylinder_body_t(ray, cap, &c.t[0]);
	c.hit[1] = near_sphere_t(ray, c.p[0], cap->radius, &c.t[1]);
	c.hit[2] = near_sphere_t(ray, c.p[1], cap->radius, &c.t[2]);
	get_best_hit(&c);
	if (c.type.error)
		return (false);
	set_final_hit(cap, hit, &c, ray);
	return (true);
}
