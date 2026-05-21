/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:24:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ray	primary_ray(const t_camera *c, float x, float y, int w, int h,
				float rx, float ry)
{
	t_ray	r;
	float	u;
	float	v;
	t_vec3	focus_p;
	t_vec3	lens_p;

	u = (2.0f * (x + 0.5f) / (float)w - 1.0f) * c->half_w;
	v = (1.0f - 2.0f * (y + 0.5f) / (float)h) * c->half_h;
	r.d = v3_norm(v3_add(c->dir,
		v3_add(v3_mul(c->right, u), v3_mul(c->up, v))));
	if (c->aperture <= 0.0f)
	{
		r.o = c->pos;
		return (r);
	}
	focus_p = v3_add(c->pos, v3_mul(r.d, c->fdist));
	lens_p = v3_add(v3_mul(c->right, rx * c->aperture),
			v3_mul(c->up, ry * c->aperture));
	r.o = v3_add(c->pos, lens_p);
	r.d = v3_norm(v3_sub(focus_p, r.o));
	return (r);
}
