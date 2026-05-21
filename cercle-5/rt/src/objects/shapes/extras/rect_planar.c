/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_planar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:54:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_rect_planar(char **t, int n, t_scene *s)
{
	t_vec3	center;
	t_vec3	normal;
	t_vec3	size;
	t_vec3	col;
	t_vec3	u;
	t_vec3	v;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;
	float	hx;
	float	hz;
	int		first;

	if (n != 5)
		return (0);
	if (!parse_vec3(t[1], &center) || !parse_unit_vec3(t[2], &normal)
		|| !parse_vec3(t[3], &size) || !parse_color(t[4], &col))
		return (0);
	basis_from_axis(normal, &u, &v);
	hx = 0.5f * size.x;
	hz = 0.5f * size.z;
	a = v3_add(center, v3_add(v3_mul(u, -hx), v3_mul(v, -hz)));
	b = v3_add(center, v3_add(v3_mul(u, hx), v3_mul(v, -hz)));
	c = v3_add(center, v3_add(v3_mul(u, hx), v3_mul(v, hz)));
	d = v3_add(center, v3_add(v3_mul(u, -hx), v3_mul(v, hz)));
	first = s->n_bvh;
	if (!push_tri(s, a, b, c, col) || !push_tri(s, a, c, d, col))
		return (0);
	s->last_kind = 1;
	s->last_first = first;
	s->last_count = 2;
	return (1);
}
