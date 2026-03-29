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
	int	mat_idx;

	if (!sha || !sha->rt || !sha->hit)
		return ;
	mat_idx = sha->hit->mat_idx;
	DBG_TRACE_MSG(DBG_CH_RENDER,
		"get_shading_material: mat_idx=%d\n", mat_idx);
	if (mat_idx < 0
		|| mat_idx >= (int)sha->rt->scene->mat_count)
	{
		DBG_WARN_MSG(DBG_CH_RENDER,
			"get_shading_material: mat_idx=%d OOB\n", mat_idx);
		return ;
	}
	sha->mat = &sha->rt->rt_materials[mat_idx];
}
