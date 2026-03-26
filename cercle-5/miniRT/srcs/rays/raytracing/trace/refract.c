/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Computes the refracted ray direction using Snell's Law and 
 * Rodrigues rotation-inspired vector form.
 */
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2)
{
	float	cosi;
	float	eta;
	float	k;
	t_vec3	part[2];

	cosi = fmaxf(-1.0f, fminf(1.0f, (float)vec3_dot(incident, normal)));
	eta = n1 / n2;
	k = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (k < 0.0f)
		return (vec3(0, 0, 0));
	part[0] = vec3_scale(incident, eta);
	part[1] = vec3_scale(normal, eta * cosi - sqrtf(k));
	return (vec3_add(part[0], part[1]));
}
