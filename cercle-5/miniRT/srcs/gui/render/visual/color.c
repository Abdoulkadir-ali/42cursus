/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	rt_unpack_color(uint32_t c)
{
	t_vec3	v;

	v.x = (double)((c >> 16) & 0xFF);
	v.y = (double)((c >> 8) & 0xFF);
	v.z = (double)(c & 0xFF);
	v.w = 0;
	return (v);
}

uint32_t	rt_pack_color(t_vec3 v)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (uint32_t)(uint8_t)v.x;
	g = (uint32_t)(uint8_t)v.y;
	b = (uint32_t)(uint8_t)v.z;
	return ((r << 16) | (g << 8) | b);
}

t_vec3i	rt_unpack_color_v(uint32_t c)
{
	t_vec3i	v;

	v.x = (int)((c >> 16) & 0xFF);
	v.y = (int)((c >> 8) & 0xFF);
	v.z = (int)(c & 0xFF);
	v.w = 0;
	return (v);
}

uint32_t	rt_pack_color_v(t_vec3i v)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (uint32_t)(uint8_t)v.x;
	g = (uint32_t)(uint8_t)v.y;
	b = (uint32_t)(uint8_t)v.z;
	return ((r << 16) | (g << 8) | b);
}
