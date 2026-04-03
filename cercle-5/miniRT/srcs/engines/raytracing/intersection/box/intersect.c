/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	get_calc(t_box *bx, const t_ray *ray, t_box_calc *c)
{
	t_vec3	oc;

	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		c->ax[0] = vec3(1, 0, 0);
	else
		c->ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(c->ax[0], &c->ax[1], &c->ax[2]);
	oc = vec3_sub(ray->origin, bx->transform.pos);
	c->p[0] = vec3_dot(oc, c->ax[0]);
	c->p[1] = vec3_dot(oc, c->ax[1]);
	c->p[2] = vec3_dot(oc, c->ax[2]);
	c->d[0] = vec3_dot(ray->direction, c->ax[0]);
	c->d[1] = vec3_dot(ray->direction, c->ax[1]);
	c->d[2] = vec3_dot(ray->direction, c->ax[2]);
	c->h[0] = bx->half_extents.x;
	c->h[1] = bx->half_extents.y;
	c->h[2] = bx->half_extents.z;
}

static bool	test_axis(t_box_calc *c, int i, double *mm, int *face)
{
	double	t[2];
	double	tmp;

	if (fabs(c->d[i]) < 1e-8)
		return (c->p[i] >= -c->h[i] && c->p[i] <= c->h[i]);
	t[0] = (-c->h[i] - c->p[i]) / c->d[i];
	t[1] = (c->h[i] - c->p[i]) / c->d[i];
	if (t[0] > t[1])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
	if (t[0] > mm[0])
	{
		mm[0] = t[0];
		*face = i;
	}
	if (t[1] < mm[1])
		mm[1] = t[1];
	return (mm[0] <= mm[1]);
}

bool	intersect_box(const t_ray *ray, t_box *bx, t_hit *hit)
{
	t_box_calc	c;
	double		mm[2];
	int			face;
	int			i;

	get_calc(bx, ray, &c);
	mm[0] = -1e30;
	mm[1] = 1e30;
	face = 0;
	i = -1;
	while (++i < 3)
		if (!test_axis(&c, i, mm, &face))
			return (false);
	if (mm[0] < 1e-6)
		return (false);
	hit->t = mm[0];
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, mm[0]));
	hit->normal = c.ax[face];
	if (c.p[face] < 0.0)
		hit->normal = vec3_scale(c.ax[face], -1.0);
	if (vec3_dot(ray->direction, hit->normal) > 0.0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
