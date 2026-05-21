/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:24:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* Cheap two-color sky gradient based on ray Y direction.
 * Returns linear values; tonemap is applied later. */

t_vec3	sky_color(t_vec3 d)
{
	float	t;
	t_vec3	zenith;
	t_vec3	horizon;
	t_vec3	ground;

	zenith = v3(0.18f, 0.32f, 0.55f);
	horizon = v3(0.55f, 0.62f, 0.72f);
	ground = v3(0.06f, 0.07f, 0.09f);
	if (d.y >= 0.0f)
	{
		t = d.y;
		if (t > 1.0f)
			t = 1.0f;
		return (v3_add(v3_mul(horizon, 1.0f - t), v3_mul(zenith, t)));
	}
	t = -d.y;
	if (t > 1.0f)
		t = 1.0f;
	return (v3_add(v3_mul(horizon, 1.0f - t), v3_mul(ground, t)));
}
