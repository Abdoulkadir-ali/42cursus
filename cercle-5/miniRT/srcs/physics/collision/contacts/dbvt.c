/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbvt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

static int	process_pair(t_scene *s, t_body_pair *p, t_contact *contacts, int c, int max_c)
{
	t_shape_pair	sp[MAX_BODY_PAIRS];

	(void)s;
	int				ns;
	int				i;

	if (!p->a->is_compound && !p->b->is_compound)
		return (narrow_dispatch_body_pair(p, contacts, c));
	ns = midphase(p, 1, sp, MAX_BODY_PAIRS);
	i = 0;
	while (i < ns && c < max_c)
	{
		c = narrow_dispatch_shape_pair(&sp[i], contacts, c);
		i++;
	}
	return (c);
}

int	gather_dbvt_contacts(t_scene *s, t_contact *contacts, int max_c)
{
	t_body_pair	pairs[MAX_BODY_PAIRS];
	int			np;
	int			i;
	int			c;

	build_dbvt(s, &s->dbvt);
	np = dbvt_query_pairs(&s->dbvt, pairs, MAX_BODY_PAIRS);
	c = 0;
	i = 0;
	while (i < np && c < max_c)
	{
		c = process_pair(s, &pairs[i], contacts, c, max_c);
		i++;
	}
	return (c);
}
