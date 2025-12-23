/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:02 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 14:46:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

#include <math.h>

double	vec2d_min(t_vec2d v)
{
	if (v.x < v.y)
		return (v.x);
	else
		return (v.y);
}

double	vec2d_max(t_vec2d v)
{
	if (v.x > v.y)
		return (v.x);
	else
		return (v.y);
}

t_vec2d	vec2d_minmax(int min, int max)
{
	return (create_vec2d(min, max));
}
