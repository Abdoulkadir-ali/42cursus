/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Return the solid theme color.
 * @param z Unused height value.
 * @return Constant white color.
 */
t_vec3	get_solid_color(int z)
{
	(void)z;
	return (create_color(255, 255, 255));
}

/**
 * @brief Return a black-or-white zebra stripe color.
 * @param z Height value used to pick the stripe parity.
 * @return Alternating zebra theme color.
 */
t_vec3	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (create_color(255, 255, 255));
	else
		return (create_color(0, 0, 0));
}

/**
 * @brief Return a neon color based on height sign.
 * @param z Height value to classify.
 * @return Green above zero, red below, blue at zero.
 */
t_vec3	get_neon_color(int z)
{
	if (z > 0)
		return (create_color(0, 255, 0));
	else if (z < 0)
		return (create_color(255, 0, 0));
	else
		return (create_color(0, 0, 255));
}
