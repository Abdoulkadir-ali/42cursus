/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:27:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	set_col(t_contact *c, t_sphere *sp, t_mesh *m)
{
	c->a = &sp->phys;
	c->ta = &sp->transform;
	c->b = &m->phys;
	c->tb = &m->transform;
	c->restitution = (sp->phys.elasticity + m->phys.elasticity) * 0.5;
	c->friction = (sp->phys.friction + m->phys.friction) * 0.5;
	c->contact_point = vec3_add(sp->phys.pos,
			vec3_scale(c->normal, sqrt(sp->radius_sq) - c->penetration));
	c->ra = vec3_sub(c->contact_point, sp->phys.pos);
	c->rb = vec3_sub(c->contact_point, m->phys.pos);
}

void	sphere_vs_mesh(t_sphere *sp, t_mesh *m, t_contact_query *q)
{
	t_collision	col;

	if (q->count >= q->max)
		return ;
	if (!detect_sphere_mesh_collision(sp, m, q->engine, &col))
		return ;
	q->contacts[q->count].normal = col.best_normal;
	q->contacts[q->count].penetration = col.best_pen;
	set_col(&q->contacts[q->count], sp, m);
	q->count++;
}
