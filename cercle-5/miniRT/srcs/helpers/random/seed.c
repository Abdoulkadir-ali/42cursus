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

uint64_t	rt_seed_pos(t_vec3 p)
{
	uint64_t	s;

	s = (uint64_t)(p.x * 73856093.0);
	s ^= (uint64_t)(p.y * 19349663.0);
	s ^= (uint64_t)(p.z * 83492791.0);
	s ^= s >> 33;
	s *= 0xff51afd7ed558ccdULL;
	s ^= s >> 33;
	s *= 0xc4ceb9fe1a85ec53ULL;
	s ^= s >> 33;
	return (s);
}

uint64_t	rt_seed_mix(uint64_t base, int frame, int id)
{
	return (base ^ (uint64_t)((uint64_t)frame * 1103515245ULL + (uint64_t)id * 374761393ULL));
}

uint64_t	rt_seed_point(t_vec3 p, int frame, int id)
{
	return (rt_seed_mix(rt_seed_pos(p), frame, id));
}
