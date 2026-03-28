/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:04:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Applies normal/bump mapping if available.
*/
void	apply_bump(t_shading *sha)
{
	t_vec3	s;
	t_vec3	m_n;
	t_vec3	n;

	if (sha->mat->normal_map_idx < 0)
		return ;
	s = sample_texture_pool(sha, sha->mat->normal_map_idx, sha->hit->u, sha->hit->v);
	m_n.x = s.x * 2.0 - 1.0;
	m_n.y = s.y * 2.0 - 1.0;
	m_n.z = s.z * 2.0 - 1.0;
	m_n.w = 0.0;
	n.x = sha->hit->tangent.x * m_n.x + sha->hit->bitangent.x * m_n.y
		+ sha->hit->normal.x * m_n.z;
	n.y = sha->hit->tangent.y * m_n.x + sha->hit->bitangent.y * m_n.y
		+ sha->hit->normal.y * m_n.z;
	n.z = sha->hit->tangent.z * m_n.x + sha->hit->bitangent.z * m_n.y
		+ sha->hit->normal.z * m_n.z;
	n.w = 0.0;
	sha->hit->normal = vec3_norm(n);
}
