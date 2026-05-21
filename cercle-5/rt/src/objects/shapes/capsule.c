/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:34:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:34:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_capsule(char **t, int n, t_scene *s)
{
	t_object	*o;
	int			ok;
	float		diam;

	if (n < 6)
		return (0);
	o = scene_push_bvh(s);
	if (!o || !parse_vec3(t[1], &o->u.cap.base)
		|| !parse_unit_vec3(t[2], &o->u.cap.axis))
		return (0);
	o->type = OBJ_CAPSULE;
	diam = ft_atof_strict(t[3], &ok);
	if (!ok || diam <= 0.0f)
		return (0);
	o->u.cap.radius = diam * 0.5f;
	o->u.cap.radius2 = o->u.cap.radius * o->u.cap.radius;
	o->u.cap.height = ft_atof_strict(t[4], &ok);
	if (!ok || o->u.cap.height < 0.0f || !parse_color(t[5], &o->color))
		return (0);
	mat_init_default(&o->mat, o->color);
	s->last_kind = 1;
	s->last_first = s->n_bvh - 1;
	s->last_count = 1;
	if (n > 6)
		return (parse_property(t + 6, n - 6, s));
	return (1);
}
