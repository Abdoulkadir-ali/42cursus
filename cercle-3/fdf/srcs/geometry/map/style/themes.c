/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 14:37:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

unsigned int	get_solid_color(int z)
{
	(void)z;
	return (0xFFFFFF); // White
}

unsigned int	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (0xFFFFFF);
	else
		return (0x000000);
}

unsigned int	get_neon_color(int z)
{
	if (z > 0)
		return (0x00FF00); // Green
	else if (z < 0)
		return (0xFF0000); // Red
	else
		return (0x0000FF); // Blue
}
