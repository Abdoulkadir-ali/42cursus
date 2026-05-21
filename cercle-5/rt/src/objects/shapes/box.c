/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_box_geo(t_object *o, char **t)
{
	t_vec3		he;
	t_vec3		ax;

	if (!parse_vec3(t[1], &o->u.box.center) || !parse_unit_vec3(t[2], &ax))
		return (0);
	if (!parse_vec3(t[3], &he) || he.x <= 0.0f || he.y <= 0.0f || he.z <= 0.0f)
		return (0);
	o->u.box.u = ax;
	basis_from_axis(ax, &o->u.box.v, &o->u.box.w);
	o->u.box.he = (t_vec3){he.x * 0.5f, he.y * 0.5f, he.z * 0.5f};
	return (1);
}

int	parse_box(char **t, int n, t_scene *s)
{
	t_object	*o;

	if (n < 5)
		return (0);
	o = scene_push_bvh(s);
	if (!o || !parse_box_geo(o, t))
		return (0);
	o->type = OBJ_BOX;
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
