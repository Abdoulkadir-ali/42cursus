/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_pyramid(char **t, int n, t_scene *s)
{
	t_object	*o;
	int			ok;

	if (n < 6)
		return (0);
	o = scene_push_bvh(s);
	if (!o || !parse_vec3(t[1], &o->u.pyr.base)
		|| !parse_unit_vec3(t[2], &o->u.pyr.axis))
		return (0);
	o->type = OBJ_PYRAMID;
	o->u.pyr.side = ft_atof_strict(t[3], &ok);
	if (!ok || o->u.pyr.side <= 0.0f)
		return (0);
	o->u.pyr.height = ft_atof_strict(t[4], &ok);
	if (!ok || o->u.pyr.height <= 0.0f || !parse_color(t[5], &o->color))
		return (0);
	o->u.pyr.apex = v3_add(o->u.pyr.base,
			v3_mul(o->u.pyr.axis, o->u.pyr.height));
	basis_from_axis(o->u.pyr.axis, &o->u.pyr.u, &o->u.pyr.v);
	mat_init_default(&o->mat, o->color);
	s->last_kind = 1;
	s->last_first = s->n_bvh - 1;
	s->last_count = 1;
	if (n > 6)
		return (parse_property(t + 6, n - 6, s));
	return (1);
}
