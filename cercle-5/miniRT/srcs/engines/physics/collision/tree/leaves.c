/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_aabb	fatten(t_aabb a)
{
	t_aabb	r;

	r.min = vec3_sub(a.min, vec3(DBVT_FAT_MARGIN, DBVT_FAT_MARGIN,
				DBVT_FAT_MARGIN));
	r.max = vec3_add(a.max, vec3(DBVT_FAT_MARGIN, DBVT_FAT_MARGIN,
				DBVT_FAT_MARGIN));
	return (r);
}

static void	push_leaf(t_dbvt *t, void *shape, t_physics_body *body,
		t_transform *ta, t_aabb aabb, t_support_fn sup, t_phys_type type)
{
	t_dbvt_leaf	*l;

	if (t->leaf_count >= DBVT_MAX_LEAVES)
		return ;
	l = &t->leaves[t->leaf_count++];
	l->shape = shape;
	l->body = body;
	l->transform = ta;
	l->fat_aabb = fatten(aabb);
	l->support = sup;
	l->type = type;
}

/**
 * @brief Collects one leaf per non-static dynamic body from the scene.
 * Called by build_dbvt() before tree construction.
 */
void	collect_leaves(t_scene *s, t_dbvt *t)
{
	int	i;

	t->leaf_count = 0;
	i = -1;
	while (++i < s->sphere_count)
		if (!s->spheres[i].phys.is_static)
			push_leaf(t, &s->spheres[i], &s->spheres[i].phys,
				&s->spheres[i].transform, sphere_aabb(&s->spheres[i]),
				gjk_support_sphere, TYPE_PHYS_SPHERE);
	i = -1;
	while (++i < s->box_count)
		if (!s->boxes[i].phys.is_static)
			push_leaf(t, &s->boxes[i], &s->boxes[i].phys,
				&s->boxes[i].transform, box_aabb(&s->boxes[i]), gjk_support_box,
				TYPE_PHYS_BOX);
	i = -1;
	while (++i < s->capsule_count)
		if (!s->capsules[i].phys.is_static)
			push_leaf(t, &s->capsules[i], &s->capsules[i].phys,
				&s->capsules[i].transform, capsule_aabb(&s->capsules[i]),
				gjk_support_capsule, TYPE_PHYS_CAPSULE);
	i = -1;
	while (++i < s->cylinder_count)
		if (!s->cylinders[i].phys.is_static)
			push_leaf(t, &s->cylinders[i], &s->cylinders[i].phys,
				&s->cylinders[i].transform, cylinder_aabb(&s->cylinders[i]),
				gjk_support_cylinder, TYPE_PHYS_CYLINDER);
	i = -1;
	while (++i < s->anim_count)
		if (!s->animated[i].base.phys.is_static)
			push_leaf(t, &s->animated[i], &s->animated[i].base.phys,
				&s->animated[i].base.transform,
				s->animated[i].base.phys.global_aabb, NULL, TYPE_PHYS_MESH);
}
