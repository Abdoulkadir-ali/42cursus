/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:07:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

size_t	bilerp_pixel(size_t c[4], t_vec4f w)
{
	float	wt;
	t_vec3f	acc;
	size_t	i;
	t_vec3f	rgb;
	float	*wf;

	wf = (float *)&w;
	wt = wf[0] + wf[1] + wf[2] + wf[3];
	if (wt < 1e-6f)
		return (c[0]);
	acc = (t_vec3f){0, 0, 0, 0};
	i = 0;
	while (i < 4)
	{
		rgb = rt_unpack_color(c[i]);
		acc.x += rgb.x * wf[i];
		acc.y += rgb.y * wf[i];
		acc.z += rgb.z * wf[i];
		i++;
	}
	acc.x /= wt;
	acc.y /= wt;
	acc.z /= wt;
	return (rt_pack_color(acc));
}
