/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

void	fbx_build_flat(t_mesh *m, t_fbx_flat_params *p)
{
	t_fbx_build	b;

	if (!p)
		return ;
	ft_print_debug("DEBUG: Starting fbx_build_flat (raw_c=%zu, vc=%zu)\n",
		p->raw_c, p->vc);
	if (!fbx_setup_build(&b, m, p))
		return ;
	fbx_build_tris(&b);
	free(b.m->vertices);
	b.m->vertices = b.vertices;
	b.m->triangles = b.triangles;
	b.m->vertex_count = b.vp;
	b.m->tri_count = b.vp / 3;
	b.vertices = NULL;
	b.triangles = NULL;
	free(b.v);
	ft_print_debug("DEBUG: fbx_build_flat final count: %zu vertices (%zu tris)\n",
		b.vp, b.vp / 3);
}
