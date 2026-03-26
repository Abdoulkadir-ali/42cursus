/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addemissive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	add_emissive_lighting(t_shading *ctx, t_scene *sc, t_vec3 *total)
{
	int				i;
	t_emissive_ref	r;

	i = -1;
	while (++i < sc->emissive_n)
	{
		r = sc->emissive_cache[i];
		if (r.type == TYPE_SPHERE || r.type == TYPE_TRI || r.type == TYPE_RECT
			|| r.type == TYPE_PYRAMID)
			emissive_primary(ctx, sc, total, r);
		else
			emissive_complex(ctx, sc, total, r);
	}
}
