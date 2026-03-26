/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:48:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	get_box_proj(t_box *bx, const t_ray *ray, t_box_ctx *c)
{
	t_vec3	oc;

	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		c->ax[0] = vec3(1, 0, 0);
	else
		c->ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(c->ax[0], &c->ax[1], &c->ax[2]);
	oc = vec3_sub(ray->origin, bx->transform.pos);
	c->h[0] = bx->half_extents.x;
	c->h[1] = bx->half_extents.y;
	c->h[2] = bx->half_extents.z;
	c->p[0] = vec3_dot(oc, c->ax[0]);
	c->p[1] = vec3_dot(oc, c->ax[1]);
	c->p[2] = vec3_dot(oc, c->ax[2]);
	c->d_ax[0] = vec3_dot(ray->direction, c->ax[0]);
	c->d_ax[1] = vec3_dot(ray->direction, c->ax[1]);
	c->d_ax[2] = vec3_dot(ray->direction, c->ax[2]);
}

static bool	check_slab(t_box_ctx *c, int i)
{
	double	ta;
	double	tb;
	double	tmp;

	if (fabs(c->d_ax[i]) < 1e-8)
		return (!(c->p[i] < -c->h[i] || c->p[i] > c->h[i]));
	ta = (-c->h[i] - c->p[i]) / c->d_ax[i];
	tb = (c->h[i] - c->p[i]) / c->d_ax[i];
	if (ta > tb)
	{
		tmp = ta;
		ta = tb;
		tb = tmp;
	}
	if (ta > c->t_min)
	{
		c->t_min = ta;
		c->face = i;
	}
	if (tb < c->t_max)
		c->t_max = tb;
	return (c->t_min <= c->t_max);
}

static bool	compute_slabs(t_box_ctx *c)
{
	int	i;

	c->t_min = -1e30;
	c->t_max = 1e30;
	c->face = 0;
	i = 0;
	while (i < 3)
	{
		if (!check_slab(c, i))
			return (false);
		i++;
	}
	return (true);
}

static void	fill_box_hit(t_hit *hit, const t_ray *ray, t_box_ctx *c)
{
	double	entry;
	t_vec3	n;

	entry = c->p[c->face] + c->t_min * c->d_ax[c->face];
	if (entry < 0.0)
		n = vec3_scale(c->ax[c->face], -1.0);
	else
		n = c->ax[c->face];
	if (vec3_dot(ray->direction, n) > 0.0)
		n = vec3_scale(n, -1.0);
	hit->t = c->t_min;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, c->t_min));
	hit->normal = n;
	hit->u = 0.5;
	hit->v = 0.5;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}

bool	intersect_box(const t_ray *ray, t_box *bx, t_hit *hit)
{
	t_box_ctx	c;

	get_box_proj(bx, ray, &c);
	if (!compute_slabs(&c) || c.t_min < 1e-6)
		return (false);
	fill_box_hit(hit, ray, &c);
	return (true);
}
