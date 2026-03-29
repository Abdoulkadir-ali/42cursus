/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:22:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	add_emissive_lighting(t_shading *sha, const t_rt_engine *rt, t_vec3 *total)
{
	int				i;
	t_emissive_ref	r;

	if (!sha || !rt || !rt->emissive_cache)
		return ;
	i = -1;
	while (++i < rt->emissive_n)
	{
		r = rt->emissive_cache[i];
		t_vec3 pos;
		if (r.type == TYPE_TRI)
			pos = vec3(rt->scene->tri_soa.vx[0][r.index], rt->scene->tri_soa.vy[0][r.index], rt->scene->tri_soa.vz[0][r.index]);
		else
			pos = vec3(rt->scene->primitives.px[r.index], rt->scene->primitives.py[r.index], rt->scene->primitives.pz[r.index]);
		if (vec3_mag_sq(vec3_sub(pos, sha->hit->point)) > r.cull_sq)
			continue ;
		if (r.type == TYPE_SPHERE || r.type == TYPE_TRI || r.type == TYPE_RECT
			|| r.type == TYPE_PYRAMID)
			emissive_primary(sha, rt, total, r);
		else
			emissive_complex(sha, rt, total, r);
	}
}
