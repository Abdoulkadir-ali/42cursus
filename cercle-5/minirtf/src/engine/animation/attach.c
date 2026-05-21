/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 21:04:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "skeletal.h"

/* Snapshot bind-pose world matrices and their inverses. They're used to
 * compute the delta transform applied to non-skinned animated primitives,
 * so the loaded geometry stays in place at t=0 regardless of hierarchy. */
static void	snapshot_bind_pose(t_animator *a)
{
	int	i;

	skel_reset_to_bind(a);
	skel_compute_world(a);
	i = -1;
	while (++i < a->n_nodes)
	{
		memcpy(a->nodes[i].bind_world, a->nodes[i].world,
			sizeof(float) * 16);
		if (skel_m4_inverse(a->nodes[i].bind_world,
				a->nodes[i].bind_world_inv) != 0)
			skel_m4_identity(a->nodes[i].bind_world_inv);
	}
}

void	skel_animator_attach(t_scene *s, t_animator *a)
{
	if (!s)
		return ;
	if (s->animator)
		skel_animator_destroy((t_animator *)s->animator);
	s->animator = a;
	if (!a)
		return ;
	if (a->n_clips > 0 && a->active < 0)
		a->active = 0;
	snapshot_bind_pose(a);
	if (a->n_clips > 0)
		a->active = 0;
	skel_reset_to_bind(a);
	skel_compute_world(a);
	skel_reskin_all(a, s);
}
