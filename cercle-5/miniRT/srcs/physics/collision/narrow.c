/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   narrow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_support_fn	get_support(t_phys_type type)
{
	if (type == TYPE_PHYS_SPHERE)
		return (gjk_support_sphere);
	if (type == TYPE_PHYS_BOX)
		return (gjk_support_box);
	if (type == TYPE_PHYS_CAPSULE)
		return (gjk_support_capsule);
	if (type == TYPE_PHYS_CYLINDER)
		return (gjk_support_cylinder);
	if (type == TYPE_PHYS_RECT)
		return (gjk_support_rect);
	if (type == TYPE_PHYS_TRI)
		return (gjk_support_tri);
	if (type == TYPE_PHYS_PYRAMID)
		return (gjk_support_pyramid);
	return (gjk_support_box);
}

/**
 * @brief Dispatcher for a non-compound body pair from DBVT.
 */
int	narrow_dispatch_body_pair(t_body_pair *p, t_contact *c, int count)
{
	t_dbvt_leaf	*la = (t_dbvt_leaf *)p->la;
	t_dbvt_leaf	*lb = (t_dbvt_leaf *)p->lb;
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	sa.data = la->shape;
	sa.support = la->support;
	sa.center = la->body->center;
	sb.data = lb->shape;
	sb.support = lb->support;
	sb.center = lb->body->center;
	return (count + gjk_make_contact(&sa, &sb,
			p->a, p->b,
			la->shape, lb->shape, &c[count]));
}

/**
 * @brief Dispatcher for a shape pair (brick vs brick or brick vs shape).
 */
int	narrow_dispatch_shape_pair(t_shape_pair *p, t_contact *c, int count)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	/* Shape A (might be a sub_shape/brick) */
	sa.data = p->sa; /* t_sub_shape or shape? Need to handle brick transform! */
	sa.support = get_support(p->sa->type);
	sa.center = vec3_add(p->ba->center, p->sa->offset);
	
	/* Shape B */
	sb.data = p->sb;
	sb.support = get_support(p->sb->type);
	sb.center = vec3_add(p->bb->center, p->sb->offset);

	return (count + gjk_make_contact(&sa, &sb,
			p->ba, p->bb,
			p->sa, p->sb, &c[count]));
}
