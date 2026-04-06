/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 16:15:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

void	fbx_build_flat(t_mesh *m, t_fbx_flat_params *p)
{
	t_fbx_build	b;

	if (!p)
		return ;
	ft_print_debug("DEBUG: Starting fbx_build_flat (raw_c=%zu, vc=%zu)\n",
		p->rv.x, p->rv.y);
	if (!fbx_setup_build(&b, m, p))
		return ;
	fbx_build_tris(&b);
	free(b.m->vertices);
	b.m->vertices = b.vertices;
	b.m->triangles = b.triangles;
	b.m->vertex_count = b.cur.x;
	b.m->tri_count = b.cur.x / 3;
	b.vertices = NULL;
	b.triangles = NULL;
	free(b.v);
	ft_print_debug("FBX flat count: %zu vertices (%zu tris)\n",
		b.cur.x, b.cur.x / 3);
}
