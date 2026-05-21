/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:38:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_plane(char **t, int n, t_scene *s)
{
	t_object	*o;

	if (n < 4)
		return (0);
	o = scene_push_plane(s);
	if (!o || !parse_vec3(t[1], &o->u.pln.point)
		|| !parse_unit_vec3(t[2], &o->u.pln.normal))
		return (0);
	o->type = OBJ_PLANE;
	if (!parse_color(t[3], &o->color))
		return (0);
	mat_init_default(&o->mat, o->color);
	s->last_kind = 2;
	s->last_first = s->n_planes - 1;
	s->last_count = 1;
	if (n > 4)
		return (parse_property(t + 4, n - 4, s));
	return (1);
}
