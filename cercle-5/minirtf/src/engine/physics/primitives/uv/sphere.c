/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:38:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	sphere_uv(const t_sphere *s, t_vec3 p, float *u, float *v)
{
	t_vec3	d;

	d = v3_mul(v3_sub(p, s->center), 1.0f / s->radius);
	*u = 0.5f + atan2f(d.z, d.x) / (2.0f * (float)M_PI);
	*v = 0.5f - asinf(ft_clampf(d.y, -1.0f, 1.0f)) / (float)M_PI;
}
