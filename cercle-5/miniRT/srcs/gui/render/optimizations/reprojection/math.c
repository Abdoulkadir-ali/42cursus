/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

t_vec2	repro_get_ndc(t_vec2i p, t_vec2i size, t_vec2 half)
{
	t_vec2	ndc;

	ndc.x = (2.0 * ((double)p.x + 0.5) / (double)size.x - 1.0) * half.x;
	ndc.y = (1.0 - 2.0 * ((double)p.y + 0.5) / (double)size.y) * half.y;
	return (ndc);
}

t_vec3	repro_get_dir(t_transform cam, t_vec2 ndc)
{
	t_vec3	dir;

	dir = vec3_add(cam.forward,
			vec3_add(vec3_scale(cam.right, ndc.x),
				vec3_scale(cam.up, ndc.y)));
	return (vec3_norm(dir));
}

bool	repro_world_to_screen(t_reproj r, t_vec3 wp, t_vec2i *out_n,
			double *out_cz)
{
	t_vec3	rel;
	double	cz;

	rel = vec3_sub(wp, r.cam.pos);
	cz = vec3_dot(rel, r.cam.forward);
	if (cz < 1e-4)
		return (false);
	out_n->x = ((vec3_dot(rel, r.cam.right) / cz / r.half.x + 1.0)
			* r.size.x * 0.5);
	out_n->y = ((1.0 - vec3_dot(rel, r.cam.up) / cz / r.half.y)
			* r.size.y * 0.5);
	if (out_cz)
		*out_cz = cz;
	return (out_n->x < r.size.x && out_n->y < r.size.y);
}
