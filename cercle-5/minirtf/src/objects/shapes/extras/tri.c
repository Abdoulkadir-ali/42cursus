/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:54:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:54:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	push_tri(t_scene *s, t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 col)
{
	t_object	*o;
	t_vec3		e1;
	t_vec3		e2;

	o = scene_push_bvh(s);
	if (!o)
		return (0);
	o->type = OBJ_TRIANGLE;
	o->u.tri.a = a;
	o->u.tri.b = b;
	o->u.tri.c = c;
	e1 = v3_sub(b, a);
	e2 = v3_sub(c, a);
	o->u.tri.n = v3_norm(v3_cross(e1, e2));
	o->color = col;
	mat_init_default(&o->mat, col);
	return (1);
}
