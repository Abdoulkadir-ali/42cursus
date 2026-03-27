/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Computes the Minkowski difference support point.
 * S = support_A(dir) - support_B(-dir).
 */
t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir,
		t_vec3 *pa, t_vec3 *pb)
{
	*pa = a->support(a, dir);
	*pb = b->support(b, vec3_scale(dir, -1.0));
	return (vec3_sub(*pa, *pb));
}
