/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackbody.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 18:47:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static float	clamp01(float v)
{
	if (v < 0.0f)
		return (0.0f);
	if (v > 1.0f)
		return (1.0f);
#include "physics.h"
	return (v);
}

t_vec3	blackbody_rgb(float kelvin)
{
	float	t;
	float	r;
	float	g;
	float	b;

	if (kelvin < 1000.0f)
		kelvin = 1000.0f;
	if (kelvin > 40000.0f)
		kelvin = 40000.0f;
	t = kelvin / 100.0f;
	if (t <= 66.0f)
	{
		r = 255.0f;
		g = 99.4708025861f * logf(t) - 161.1195681661f;
	}
	else
	{
		r = 329.698727446f * powf(t - 60.0f, -0.1332047592f);
		g = 288.1221695283f * powf(t - 60.0f, -0.0755148492f);
	}
	if (t >= 66.0f)
		b = 255.0f;
	else if (t <= 19.0f)
		b = 0.0f;
	else
		b = 138.5177312231f * logf(t - 10.0f) - 305.0447927307f;
	return (v3(clamp01(r / 255.0f), clamp01(g / 255.0f), clamp01(b / 255.0f)));
}

t_vec3	emissive_color(const t_material *m)
{
	t_vec3	c;
	float	heat;

	if (!m || m->emission <= 0.0f || m->temperature <= 0.0f)
		return (v3(0, 0, 0));
	c = blackbody_rgb(m->temperature);
	/* heat-driven intensity (Stefan-like, normalized at 3000 K) */
	heat = m->temperature / 3000.0f;
	heat = heat * heat;
	return (v3_mul(c, m->emission * heat));
}