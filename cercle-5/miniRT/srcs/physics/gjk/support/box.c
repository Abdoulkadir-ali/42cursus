/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief GJK support point for an oriented box.
 */
t_vec3	gjk_support_box(const void *data, t_vec3 dir)
{
	const t_box	*bx;
	t_vec3		ax[3];
	t_vec3		p;
	int			i;

	bx = (const t_box *)data;
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	p = bx->phys.center;
	i = -1;
	while (++i < 3)
	{
		if (vec3_dot(ax[i], dir) >= 0.0)
			p = vec3_add(p, vec3_scale(ax[i], ((double *)&bx->half_extents)[i]));
		else
			p = vec3_sub(p, vec3_scale(ax[i], ((double *)&bx->half_extents)[i]));
	}
	return (p);
}
