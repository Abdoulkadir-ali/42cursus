/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:04:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD simplification: Replace the entire per-type dispatch.
 * mat_id comes directly from the hit record.
 */
void	get_shading_material(t_shading *sha)
{
	if (!sha || !sha->rt || !sha->hit)
		return ;
	
	/* Correct assignment for const pointer context */
	sha->mat = &sha->rt->rt_materials[sha->hit->mat_idx];
}
