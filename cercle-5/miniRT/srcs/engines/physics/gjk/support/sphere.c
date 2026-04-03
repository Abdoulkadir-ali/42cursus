/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest point of a sphere along the search direction.
 */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir)
{
	const t_sphere	*sp;
	t_vec3			nd;
	double			len;

	sp = (const t_sphere *)data;
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (sp->transform.pos);
	nd = vec3_scale(dir, 1.0 / len);
	return (vec3_add(sp->transform.pos, vec3_scale(nd, sqrt(sp->radius_sq))));
}
