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
	t_support_fn	sa;
	t_support_fn	sb;
	int				pia, pib;

	pia = a->scene->primitives.phys_idx[a->idx];
	pib = b->scene->primitives.phys_idx[b->idx];
	if (pia >= 0 && a->scene->physics->soa->is_compound[pia])
		sa = gjk_support_compound;
	else
		sa = get_support((t_phys_type)a->scene->primitives.types[a->idx]);
	if (pib >= 0 && b->scene->physics->soa->is_compound[pib])
		sb = gjk_support_compound;
	else
		sb = get_support((t_phys_type)b->scene->primitives.types[b->idx]);
	*pa = sa(a, dir);
	*pb = sb(b, vec3_scale(dir, -1.0));
	return (vec3_sub(*pa, *pb));
}
