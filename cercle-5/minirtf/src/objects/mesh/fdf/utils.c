/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "fdf.h"

int	fdf_push_tri(t_scene *s, t_vec3 *v, t_vec3 col)
{
	t_object	*o;
	t_vec3		e1;
	t_vec3		e2;

	o = scene_push_bvh(s);
	if (!o)
		return (-1);
	o->type = OBJ_TRIANGLE;
	o->u.tri.a = v[0];
	o->u.tri.b = v[1];
	o->u.tri.c = v[2];
	e1 = v3_sub(v[1], v[0]);
	e2 = v3_sub(v[2], v[0]);
	o->u.tri.n = v3_norm(v3_cross(e1, e2));
	o->color = col;
	mat_init_default(&o->mat, col);
	return (0);
}
