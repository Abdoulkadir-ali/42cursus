/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbvt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static int	process_pair(t_scene *s, t_body_pair *p, t_contact *contacts, int c, int max_c)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	/* For now, we handle simple pairs. Compound pairs need a dedicated loop. */
	sa.scene = s;
	sa.idx = p->idx_a;
	sb.scene = s;
	sb.idx = p->idx_b;
	return (c + gjk_make_contact(&sa, &sb, p->idx_a, p->idx_b, &contacts[c]));
}

int	gather_dbvt_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	t_body_pair	pairs[MAX_BODY_PAIRS];
	int			np;
	int			i;
	int			c;
	t_physics	*phys = s->physics;

	if (!phys)
		return (0);
	build_dbvt(s, &phys->dbvt);
	np = dbvt_query_pairs(&phys->dbvt, pairs, MAX_BODY_PAIRS);
	c = 0;
	i = 0;
	while (i < np && c < max_c)
	{
		c = process_pair(s, &pairs[i], contacts, c, max_c);
		i++;
	}
	return (c);
}
