/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	cylinder_precompute(t_cylinder *cy)
{
	cy->radius_sq = cy->transform.scale.x * cy->transform.scale.x;
	cy->top = vec3_add(cy->transform.pos,
			vec3_scale(cy->transform.forward, cy->transform.scale.y));
	vec3_orthonormal_basis(cy->transform.forward, &cy->local_u, &cy->local_v);
}
