/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seed.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 15:18:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

uint32_t	rt_seed_pos(t_vec3 p)
{
	uint32_t	s;

	s = (uint32_t)(p.x * 73856093.0);
	s ^= (uint32_t)(p.y * 19349663.0);
	s ^= (uint32_t)(p.z * 83492791.0);
	s ^= s >> 16;
	s *= 0x85ebca6b;
	s ^= s >> 13;
	s *= 0xc2b2ae35;
	s ^= s >> 16;
	return (s);
}

uint32_t	rt_seed_mix(uint32_t base, int frame, int id)
{
	return (base ^ (uint32_t)(frame * 1103515245 + id * 374761393));
}

uint32_t	rt_seed_point(t_vec3 p, int frame, int id)
{
	return (rt_seed_mix(rt_seed_pos(p), frame, id));
}
