/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern int	test_brick_pair(t_body_pair *pair, t_shape_pair *out, int count, int max);

/**
 * @brief Brick-level AABB midphase filter.
 * Public entry point for midphase collision queries.
 * Compliance: Returns count of pairs (Piège A Fix) and offloads loops (Piège C).
 */
int	midphase(t_body_pair *pairs, int n, t_shape_pair *out, int max)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n && count < max)
	{
		count = test_brick_pair(&pairs[i], out, count, max);
		i++;
	}
	return (count);
}
