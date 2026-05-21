/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_aabb	sphere_bounds(const t_sphere *s)
{
	t_aabb	b;
	t_vec3	r;

	r = v3(s->radius, s->radius, s->radius);
	b.min = v3_sub(s->center, r);
	b.max = v3_add(s->center, r);
	return (b);
}
