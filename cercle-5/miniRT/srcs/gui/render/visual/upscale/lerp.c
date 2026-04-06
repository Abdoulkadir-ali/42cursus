/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

uint32_t	bilerp_pixel(uint32_t c[4], float w[4])
{
	float	wt;
	t_vec3	acc;
	int		i;
	t_vec3	rgb;

	wt = w[0] + w[1] + w[2] + w[3];
	if (wt < 1e-6f)
		return (c[0]);
	acc = (t_vec3){0, 0, 0, 0};
	i = -1;
	while (++i < 4)
	{
		rgb = rt_unpack_color(c[i]);
		acc.x += rgb.x * w[i];
		acc.y += rgb.y * w[i];
		acc.z += rgb.z * w[i];
	}
	acc.x /= wt;
	acc.y /= wt;
	acc.z /= wt;
	return (rt_pack_color(acc));
}
