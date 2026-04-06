/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:50:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_gjk_shape	init_gjk_shape(const void *data, t_support_fn support,
		t_vec3 center)
{
	t_gjk_shape	s;

	s.data = data;
	s.support = support;
	s.center = center;
	return (s);
}

t_contact_query	init_contact_query(t_physic_engine *engine,
		t_contact *contacts, size_t count, size_t max)
{
	t_contact_query	q;

	q.engine = engine;
	q.contacts = contacts;
	q.count = count;
	q.max = max;
	return (q);
}

t_edge	init_edge(size_t a, size_t b)
{
	t_edge	e;

	e.a = a;
	e.b = b;
	return (e);
