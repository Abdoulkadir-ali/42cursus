/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 10:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Fills derived contact properties (restitution, friction).
 */
static void	fill_props(t_col_pair *p, t_contact *c)
{
	double	rb_f;
	double	rb_e;

	rb_f = 0.5;
	rb_e = 0.5;
	if (p->bb)
	{
		rb_f = p->bb->friction;
		rb_e = p->bb->elasticity;
	}
	c->restitution = fmin(p->ba->elasticity, rb_e);
	c->friction = sqrt(p->ba->friction * rb_f);
}

/**
 * @brief Unified narrow phase: GJK -> EPA.
 */
bool	gjk_make_contact(t_col_pair *p, t_contact *c)
{
	t_simplex	simplex;
	t_epa_res	res;
	t_vec3		cpt;

	if (!gjk_intersect(p->sa, p->sb, &simplex) || !gjk_epa(p, &simplex, &res))
		return (false);
	if (res.depth < 1e-9)
		return (false);
	cpt = vec3_scale(vec3_add(res.contact_a, res.contact_b), 0.5);
	c->normal = res.normal;
	c->penetration = res.depth;
	c->a = p->ba;
	c->b = p->bb;
	c->ta = p->ta;
	c->tb = p->tb;
	c->contact_point = cpt;
	c->ra = vec3_sub(cpt, p->ba->center);
	c->rb = vec3(0, 0, 0);
	if (p->bb)
		c->rb = vec3_sub(cpt, p->bb->center);
	fill_props(p, c);
	return (true);
}

/**
 * @brief Specialized contact test between a GJK shape and a static plane.
 */
bool	gjk_vs_plane(t_col_pair *p, t_plane *pl, t_contact *c)
{
	t_vec3	n;
	t_vec3	supp;
	double	dist;

	n = vec3_norm(pl->transform.up);
	supp = p->sa->support(p->sa->data, vec3_scale(n, -1.0));
	dist = vec3_dot(vec3_sub(supp, pl->transform.pos), n);
	if (dist >= 0.0)
		return (false);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -dist;
	c->a = p->ba;
	c->b = NULL;
	c->ta = p->ta;
	c->tb = &pl->transform;
	c->contact_point = supp;
	c->ra = vec3_sub(supp, p->ba->center);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(p->ba->elasticity, 0.5);
	c->friction = sqrt(p->ba->friction * 0.5);
	return (true);
}
