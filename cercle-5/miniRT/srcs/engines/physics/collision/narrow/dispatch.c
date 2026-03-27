/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern t_support_fn	get_support(t_phys_type type);

/**
 * @brief Dispatches collision resolution for a pair of dynamic actors.
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
			(t_transform *)la->shape, (t_transform *)lb->shape, &c[count]));
}

/**
 * @brief Dispatches collision resolution for internal compound bricks.
 */
int	narrow_dispatch_shape_pair(t_shape_pair *p, t_contact *c, int count)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	sa.data = p->sa;
	sa.support = get_support(p->sa->type);
	sa.center = vec3_add(p->ba->center, p->sa->offset);
	sb.data = p->sb;
	sb.support = get_support(p->sb->type);
	sb.center = vec3_add(p->bb->center, p->sb->offset);
	return (count + gjk_make_contact(&sa, &sb,
			p->ba, p->bb,
			(t_transform *)p->sa, (t_transform *)p->sb, &c[count]));
}
