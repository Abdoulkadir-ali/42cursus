/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

float	halton(int i, int b)
{
	float	f;
	float	r;

	f = 1.0f;
	r = 0.0f;
	while (i > 0)
	{
		f /= (float)b;
		r += f * (float)(i % b);
		i /= b;
	}
	return (r);
}

void	basis_from_axis(t_vec3 axis, t_vec3 *u, t_vec3 *v)
{
	t_vec3	a;

	if (fabsf(axis.y) < 0.99f)
		a = (t_vec3){0, 1, 0};
	else
		a = (t_vec3){1, 0, 0};
	*u = v3_norm(v3_cross(axis, a));
	*v = v3_norm(v3_cross(axis, *u));
}

int	ft_argb(float r, float g, float b)
{
	int	ir;
	int	ig;
	int	ib;

	ir = (int)(ft_clampf(r, 0.0f, 1.0f) * 255.0f + 0.5f);
	ig = (int)(ft_clampf(g, 0.0f, 1.0f) * 255.0f + 0.5f);
	ib = (int)(ft_clampf(b, 0.0f, 1.0f) * 255.0f + 0.5f);
	return ((ir << 16) | (ig << 8) | ib);
}
