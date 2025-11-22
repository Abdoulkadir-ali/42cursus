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

#include "map.h"

int	get_solid_color(int z)
{
	(void)z;
	return (0xFF6B35);
}

int	get_zebra_color(int z)
{
	if (z % 2 == 0)
		return (0xFFFFFF);
	return (0x00FFFF);
}

int	get_neon_color(int z)
{
	int	colors[5];

	colors[0] = 0xFF00FF;
	colors[1] = 0x00FFFF;
	colors[2] = 0xFFFF00;
	colors[3] = 0xFF0080;
	colors[4] = 0x00FF80;
	if (z < 0)
		z = -z;
	return (colors[z % 5]);
}
