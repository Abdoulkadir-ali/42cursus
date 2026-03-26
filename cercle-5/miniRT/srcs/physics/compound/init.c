/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern void	compute_com(t_physics_body *b);
extern void	compute_inertia(t_physics_body *b);
extern void	update_compound(t_physics_body *b);

/**
 * @brief Initializes a compound body from an array of Lego bricks.
 * Combines sub-shapes into a single actor with shared mass properties.
 */
void	init_compound(t_physics_body *b, t_sub_shape *bricks, size_t n)
{
	size_t	i;

	if (!b || !bricks)
		return ;
	if (n > MAX_SUB_SHAPES)
		n = MAX_SUB_SHAPES;
	i = 0;
	while (i < n)
	{
		b->sub_shapes[i] = bricks[i];
		i++;
	}
	b->sub_count = n;
	b->is_compound = true;
	compute_com(b);
	compute_inertia(b);
	update_compound(b);
}
