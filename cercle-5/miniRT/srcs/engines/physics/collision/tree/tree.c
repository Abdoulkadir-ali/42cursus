/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Public entry point. Rebuilds the DBVT from scratch each frame.
 * Strategy: collect leaves → sort by centroid on longest axis (via
 *            median-split in dbvt_build_range) → link nodes.
 * Full rebuild is O(n log n) and fast for typical scene sizes (< 256 bodies).
 */
void	build_dbvt(t_scene *s, t_dbvt *t)
{
	t->node_count = 0;
	t->leaf_count = 0;
	t->root = DBVT_NULL;
	collect_leaves(s, t);
	if (t->leaf_count == 0)
		return ;
	t->root = dbvt_build_range(t, 0, t->leaf_count);
}
