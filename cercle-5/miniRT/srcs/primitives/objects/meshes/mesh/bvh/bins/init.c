/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:13:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Initializes a bin array for BVH construction.
 */
void	bvh_bins_init(t_bin *bins)
{
	int	i;

	i = 0;
	while (i < BVH_BINS)
	{
		bins[i].count = 0;
		bins[i].bounds = aabb_create_empty();
		i++;
	}
}
