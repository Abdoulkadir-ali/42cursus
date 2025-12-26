/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:06:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

unsigned int	vecu3_len(t_vecu3 v)
{
	return ((unsigned int)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

unsigned int	vecu3_min(t_vecu3 v)
{
	unsigned int	min;

	min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;
	return (min);
}

unsigned int	vecu3_max(t_vecu3 v)
{
	unsigned int	max;

	max = v.x;
	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;
	return (max);
}
