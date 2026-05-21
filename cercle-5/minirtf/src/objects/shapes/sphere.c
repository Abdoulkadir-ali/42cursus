/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:37:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_sphere(char **t, int n, t_scene *s)
{
	t_object	*o;
	int			ok;
	float		diam;

	if (n < 4)
		return (0);
	o = scene_push_bvh(s);
	if (!o || !parse_vec3(t[1], &o->u.sph.center))
		return (0);
	o->type = OBJ_SPHERE;
	diam = ft_atof_strict(t[2], &ok);
	if (!ok || diam <= 0.0f || !parse_color(t[3], &o->color))
		return (0);
	o->u.sph.radius = diam * 0.5f;
	o->u.sph.radius2 = o->u.sph.radius * o->u.sph.radius;
	mat_init_default(&o->mat, o->color);
	s->last_kind = 1;
	s->last_first = s->n_bvh - 1;
	s->last_count = 1;
	if (n > 4)
		return (parse_property(t + 4, n - 4, s));
	return (1);
}
