/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:21:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

/* Build the per-skin joint palette: palette[j] = world(joint_j) * IBM[j].
 * Used by skel_skin_vertex when blending weighted positions. */
void	skel_build_palette(t_animator *a, int skin_idx)
{
	const t_anim_skin	*s;
	int					j;
	int					jn;

	s = &a->skins[skin_idx];
	j = -1;
	while (++j < s->n_joints)
	{
		jn = s->joints[j];
		if (jn < 0 || jn >= a->n_nodes)
			skel_m4_identity(&a->joint_mats[j * 16]);
		else
			skel_m4_mul(a->nodes[jn].world, &s->ibm[j * 16], &a->joint_mats[j
				* 16]);
	}
}
