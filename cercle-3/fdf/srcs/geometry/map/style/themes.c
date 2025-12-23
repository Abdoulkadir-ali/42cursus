/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 14:46:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec3	get_solid_color(int z)
{
	(void)z;
	return (create_color(255, 255, 255));
}

t_vec3	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (create_color(255, 255, 255));
	else
		return (create_color(0, 0, 0));
}

t_vec3	get_neon_color(int z)
{
	if (z > 0)
		return (create_color(0, 255, 0));
	else if (z < 0)
		return (create_color(255, 0, 0));
	else
		return (create_color(0, 0, 255));
}
