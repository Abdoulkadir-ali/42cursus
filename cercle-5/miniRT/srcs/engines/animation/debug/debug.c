/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"
#include <stdio.h>

/**
 * Print skeleton hierarchy for debugging purposes.
 */
void	anim_debug_print_skeleton(t_skinned_mesh *sm)
{
	int		i;
	t_bone	*b;

	printf("--- Skeleton Debug (Bones: %d) ---\n", sm->bone_count);
	i = 0;
	while (i < sm->bone_count)
	{
		b = &sm->skeleton[i];
		printf("Bone[%d]: NodeIdx=%d, ParentIdx=%d\n", i, b->node_idx, b->parent);
		i++;
	}
	printf("----------------------------------\n");
}
