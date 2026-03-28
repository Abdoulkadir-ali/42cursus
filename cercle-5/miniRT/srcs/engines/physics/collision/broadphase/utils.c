/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:04:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:04:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

bool	aabb_overlap_broad(t_aabb a, t_aabb b)
{
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0])
		return (false);
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1])
		return (false);
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2])
		return (false);
	return (true);
}
