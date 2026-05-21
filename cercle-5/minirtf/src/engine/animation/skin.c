/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

/* Non-skinned prims: positions are in mesh-local space. The loader emitted
 * `outer(node.bind_world * mesh_local)`. Apply current `node.world` to the
 * mesh-local position so animated TRS reaches the renderer; outer is layered
 * on top by `apply_outer`. At bind, world == bind_world and the result
 * matches the loader exactly. */
static t_vec3	skin_static(const t_animator *a, const t_anim_prim *p,
			t_vec3 v)
{
	if (p->node < 0 || p->node >= a->n_nodes)
		return (v);
	return (skel_m4_xform_pos(a->nodes[p->node].world, v));
}

static t_vec3	skin_blend(const t_animator *a, const t_anim_prim *p,
			t_vec3 pos, int v)
{
	t_vec3			acc;
	float			w_sum;
	unsigned int	j;
	float			w;
	int				i;

	acc = (t_vec3){0, 0, 0};
	w_sum = 0;
	i = -1;
	while (++i < 4)
	{
		j = p->joints[v * 4 + i];
		w = p->weights[v * 4 + i];
		if (w <= 0.0f || (int)j >= a->skins[p->skin].n_joints)
			continue ;
		acc = v3_add(acc, v3_mul(skel_m4_xform_pos(
						&a->joint_mats[j * 16], pos), w));
		w_sum += w;
	}
	if (w_sum < 1e-6f)
		return (skin_static(a, p, pos));
	return (acc);
}

t_vec3	skel_skin_vertex(const t_animator *a, const t_anim_prim *p, int v)
{
	t_vec3	pos;

	pos = (t_vec3){p->positions[v * 3], p->positions[v * 3 + 1],
		p->positions[v * 3 + 2]};
	if (p->skin < 0 || !p->joints || !p->weights)
		return (skin_static(a, p, pos));
	return (skin_blend(a, p, pos, v));
}
