/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:36:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_triangle(char **t, int n, t_scene *s)
{
	t_object	*o;
	t_vec3		e[2];

	if (n < 5)
		return (0);
	o = scene_push_bvh(s);
	if (!o || !parse_vec3(t[1], &o->u.tri.a) || !parse_vec3(t[2], &o->u.tri.b)
		|| !parse_vec3(t[3], &o->u.tri.c))
		return (0);
	o->type = OBJ_TRIANGLE;
	e[0] = v3_sub(o->u.tri.b, o->u.tri.a);
	e[1] = v3_sub(o->u.tri.c, o->u.tri.a);
	o->u.tri.n = v3_norm(v3_cross(e[0], e[1]));
	if (!parse_color(t[4], &o->color))
		return (0);
	mat_init_default(&o->mat, o->color);
	s->last_kind = 1;
	s->last_first = s->n_bvh - 1;
	s->last_count = 1;
	if (n > 5)
		return (parse_property(t + 5, n - 5, s));
	return (1);
}
