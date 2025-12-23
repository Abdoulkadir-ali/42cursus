/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:02 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 12:48:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

int	vec2_len(t_vec2 v)
{
	return ((int)sqrt(v.x * v.x + v.y * v.y));
}

int	vec2_min(t_vec2 v)
{
	if (v.x < v.y)
		return (v.x);
	return (v.y);
}

int	vec2_max(t_vec2 v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}

t_vec2	vec2_minmax(int min, int max)
{
	return (create_vec2(min, max));
}
