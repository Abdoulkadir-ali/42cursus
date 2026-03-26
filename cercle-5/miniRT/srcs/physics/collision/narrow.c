/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   narrow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_gjk_shape	get_gjk_shape(t_dbvt_leaf *l)
{
	t_gjk_shape	s;

	s.data = l->shape;
	s.support = l->support;
	s.center = l->body->center;
	return (s);
}

static int	dispatch_plane(t_dbvt_leaf *a, t_dbvt_leaf *b,
		t_contact *c, int count)
{
	t_gjk_shape sa = get_gjk_shape(a);
	(void)b;
	return (count + gjk_vs_plane(&sa, a->body, NULL, NULL, c));
}

/**
 * @brief Narrowphase dispatcher for a DBVT body pair.
 * Selects GJK based on both shape types. Returns new contact count.
 * Both shapes must be non-static (guaranteed by leaf collection).
 */
int	narrow_dispatch(t_dbvt_leaf *a, t_dbvt_leaf *b,
		t_contact *c, int count)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	(void)dispatch_plane;
	if (!a || !b || !c) return (count);
	sa = get_gjk_shape(a);
	sb = get_gjk_shape(b);
	count += gjk_make_contact(&sa, &sb,
			a->body, b->body,
			(void *)a->shape, (void *)b->shape, &c[count]);
	return (count);
}
