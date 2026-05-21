/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:20:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

int	push_back_to_scene(t_app *app)
{
	int			moved;
	int			i;
	t_body		*b;
	t_object	*o;
	float		heat_glow;
	t_vec3		old;
	t_vec3		dd;

	moved = 0;
	i = 0;
	while (i < app->phys.n)
	{
		b = &app->phys.bodies[i];
		if (b->sphere_idx >= 0 && (size_t)b->sphere_idx < app->scene.n_bvh)
		{
			o = &app->scene.bvh_objs[b->sphere_idx];
			if (b->inv_mass > 0.0f)
			{
				old = object_center(o);
				object_translate_to(o, b->pos);
				dd = v3_sub(b->pos, old);
				if (v3_dot(dd, dd) > 1e-10f)
					moved = 1;
			}
			o->mat.temperature = b->temperature;
			if (b->temperature > 800.0f)
			{
				heat_glow = (b->temperature - 800.0f) / 1500.0f;
				if (heat_glow > 4.0f)
					heat_glow = 4.0f;
				if (heat_glow > o->mat.emission)
					o->mat.emission = heat_glow;
			}
		}
		i++;
	}
	return (moved);
}
