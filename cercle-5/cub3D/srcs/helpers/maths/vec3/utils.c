/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:25:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	normalize_vec3(t_vec3 a)
{
	float	mag;

	mag = vec3_mag(a);
	if (mag == 0.0f)
		return (a);
	return ((t_vec3){a.x / mag, a.y / mag, a.z / mag});
}

t_vec3i	vec3i_scale(t_vec3i v, int s)
{
	return ((t_vec3i){v.x * s, v.y * s, v.z * s});
}
