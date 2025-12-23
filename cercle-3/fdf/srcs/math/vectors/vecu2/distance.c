/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:55:00 by abdoali          ###   ########.fr       */
/*   Updated: 2025/12/21 00:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

unsigned int	vecu2_len(t_vecu2 v)
{
	return ((unsigned int)sqrt(v.x * v.x + v.y * v.y));
}

unsigned int	vecu2_min(t_vecu2 v)
{
	if (v.x < v.y)
		return (v.x);
	return (v.y);
}

unsigned int	vecu2_max(t_vecu2 v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}
