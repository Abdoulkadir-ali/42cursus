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
		if (r.type == TYPE_SPHERE || r.type == TYPE_TRI || r.type == TYPE_RECT
			|| r.type == TYPE_PYRAMID)
			emissive_primary(sha, rt, total, r);
		else
			emissive_complex(sha, rt, total, r);
	}
}
