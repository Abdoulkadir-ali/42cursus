/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 20:09:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

static int	node_depth(const t_animator *a, int n)
{
	int	d;

	d = 0;
	while (n >= 0 && a->nodes[n].parent >= 0 && d < 4096)
	{
		n = a->nodes[n].parent;
		d++;
	}
	return (d);
}

static void	update_node_world(t_animator *a, int i)
{
	t_mat4	local;
	int		j;

	if (a->nodes[i].has_matrix)
		memcpy(local, a->nodes[i].local_mat, sizeof(local));
	else
		skel_m4_from_trs(&a->nodes[i].t, &a->nodes[i].r,
			&a->nodes[i].s, local);
	if (a->nodes[i].parent < 0)
		memcpy(a->nodes[i].world, local, sizeof(local));
	else
	{
		j = a->nodes[i].parent;
		skel_m4_mul(a->nodes[j].world, local, a->nodes[i].world);
	}
}

void	skel_compute_world(t_animator *a)
{
	int	i;
	int	max_d;
	int	d;

	max_d = 0;
	i = 0;
	while (i < a->n_nodes)
	{
		d = node_depth(a, i);
		if (d > max_d)
			max_d = d;
		i++;
	}
	d = 0;
	while (d <= max_d)
	{
		i = 0;
		while (i < a->n_nodes)
		{
			if (node_depth(a, i) == d)
				update_node_world(a, i);
			i++;
		}
		d++;
	}
}

void	skel_reset_to_bind(t_animator *a)
{
	int	i;

	i = 0;
	while (i < a->n_nodes)
	{
		a->nodes[i].t = a->nodes[i].bt;
		a->nodes[i].r = a->nodes[i].br;
		a->nodes[i].s = a->nodes[i].bs;
		i++;
	}
}
