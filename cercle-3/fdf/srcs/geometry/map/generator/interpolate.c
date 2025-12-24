/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:12:48 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:22:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

float	fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	lerp(float t, float a, float b)
{
	return (a + t * (b - a));
}

t_vec2d	lerp_vec(float t, t_vec2d a, t_vec2d b)
{
	t_vec2d	result;

	result.x = a.x + t * (b.x - a.x);
	result.y = a.y + t * (b.y - a.y);
	return (result);
}

float	grad(t_noise_state *state, int hash, float x, float y)
{
	int		h;
	t_vec2d	g;

	h = hash & 255;
	g = state->grads[h];
	return (g.x * x + g.y * y);
}
