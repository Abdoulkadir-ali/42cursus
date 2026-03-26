/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"

/**
 * @brief GJK support point for a triangle. Uses pre-built world-space verts.
 */
t_vec3	gjk_support_tri(const void *data, t_vec3 dir)
{
	const t_tri_shape	*tr;

	tr = (const t_tri_shape *)data;
	return (gjk_support_list(tr->v, 3, dir));
}
