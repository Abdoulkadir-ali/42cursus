/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief GJK support point for a sphere.
 */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir)
{
	const t_sphere	*sp;
	double			len;

	sp = (const t_sphere *)data;
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (sp->transform.pos);
	return (vec3_add(sp->transform.pos, vec3_scale(dir,
				sqrt(sp->radius_sq) / len)));
}
