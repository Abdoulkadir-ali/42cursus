/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:16:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	ft_swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	box_compute_t(t_vec3 t_min, t_vec3 t_max, double *min_t, double *max_t)
{
	if (t_min.x > t_max.x)
		ft_swap_double(&t_min.x, &t_max.x);
	if (t_min.x > *min_t)
		*min_t = t_min.x;
	if (t_max.x < *max_t)
		*max_t = t_max.x;
	if (t_min.y > t_max.y)
		ft_swap_double(&t_min.y, &t_max.y);
	if (t_min.y > *min_t)
		*min_t = t_min.y;
	if (t_max.y < *max_t)
		*max_t = t_max.y;
	if (t_min.z > t_max.z)
		ft_swap_double(&t_min.z, &t_max.z);
	if (t_min.z > *min_t)
		*min_t = t_min.z;
	if (t_max.z < *max_t)
		*max_t = t_max.z;
}

static void	box_set_hit(t_hit *hit, t_box bx, t_ray ray, double t)
{
	t_vec3	d;
	t_vec3	h;

	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	d = vec3_sub(hit->point, vec3_scale(vec3_add(bx.min, bx.max), 0.5));
	h = vec3_scale(vec3_sub(bx.max, bx.min), 0.5);
	hit->normal = vec3(0, 0, 0);
	if (fabs(d.x - h.x) < 0.001)
		hit->normal.x = 1;
	else if (fabs(d.x + h.x) < 0.001)
		hit->normal.x = -1;
	else if (fabs(d.y - h.y) < 0.001)
		hit->normal.y = 1;
	else if (fabs(d.y + h.y) < 0.001)
		hit->normal.y = -1;
	else if (fabs(d.z - h.z) < 0.001)
		hit->normal.z = 1;
	else if (fabs(d.z + h.z) < 0.001)
		hit->normal.z = -1;
	hit->mat_idx = bx.mat_idx;
	hit->type = TYPE_BOX;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}

bool	intersect_box(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_box	bx;
	double	min_t;
	double	max_t;
	t_vec2	t;

	bx = unpack_box(p, i);
	min_t = -1e30;
	max_t = 1e30;
	box_compute_t(vec3_mul(vec3_sub(bx.min, ray->origin), ray->inv_dir),
		vec3_mul(vec3_sub(bx.max, ray->origin), ray->inv_dir), &min_t, &max_t);
	if (min_t > max_t || max_t < EPSILON)
		return (false);
	t.x = min_t;
	if (min_t <= EPSILON)
		t.x = max_t;
	box_set_hit(hit, bx, *ray, t.x);
	return (true);
}
