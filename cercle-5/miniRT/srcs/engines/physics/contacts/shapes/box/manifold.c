/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manifold.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:42:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Writes a single manifold contact point into the query's contact array.
 *        Copies the base contact (normal, restitution, friction, body pointers)
 *        and overrides the geometric fields for this specific contact point.
 */
static void	add_manifold_pt(t_contact_query *qu, t_contact *base,
		t_vec3 pt, double depth)
{
	t_contact	*c;

	c = &qu->contacts[qu->count];
	*c = *base;
	c->contact_point = pt;
	c->penetration = depth;
	c->ra = vec3_sub(pt, base->a->center);
	if (base->b)
		c->rb = vec3_sub(pt, base->b->center);
	qu->count++;
}

/**
 * @brief Probes each corner of box B's incident face against the reference
 *        plane on box A. Corners at or below the plane become contact points,
 *        yielding up to 4 contacts for flat face-to-face resting.
 */
static void	build_manifold(t_contact_query *qu, t_box *ba,
		t_box *bb, t_contact *base)
{
	t_vec3	ref_v[4];
	t_vec3	inc[4];
	t_vec3	ref_n;
	double	d[2];
	size_t	i;

	ref_n = best_box_face_verts(ba, base->normal, ref_v);
	d[0] = vec3_dot(ref_n, ref_v[0]);
	best_box_face_verts(bb, vec3_scale(base->normal, -1.0), inc);
	i = 0;
	while (i < 4 && qu->count < qu->max)
	{
		d[1] = d[0] - vec3_dot(ref_n, inc[i]);
		if (d[1] >= -1e-4)
			add_manifold_pt(qu, base, inc[i], fmax(d[1], 0.0));
		i++;
	}
}

/**
 * @brief Generates a contact manifold (up to 4 points) for a box-vs-box pair.
 *        Uses the EPA-provided collision normal to find the reference face on A
 *        and incident face on B, then probes each corner of B's face against
 *        A's reference plane. Falls back to the single GJK contact if no
 *        corners are found (edge/vertex-only touches).
 */
size_t	box_vs_box_manifold(t_contact_query *qu, t_box *ba,
		t_box *bb, t_contact *base)
{
	size_t	old_count;

	old_count = qu->count;
	build_manifold(qu, ba, bb, base);
	if (qu->count == old_count && qu->count < qu->max)
		qu->contacts[qu->count++] = *base;
	return (qu->count);
}
