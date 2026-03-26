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

#include "objects.h"

void	fbx_build_flat(t_mesh *m, t_fbx_flat_args *p)
{
	t_fbx_build	b;

	if (!p)
		return ;
	ft_print_debug("DEBUG: Starting fbx_build_flat (raw_c=%d, vc=%d)\n",
		p->raw_c, p->vc);
	if (!fbx_setup_build(&b, m, p))
		return ;
	fbx_build_tris(&b);
	free(b.m->vertices);
	b.m->vertices = b.nv;
	b.m->normals = b.nn;
	b.m->uvs = b.nu;
	b.m->indices = b.ni;
	b.m->vertex_count = b.vp;
	b.m->tri_count = b.vp / 3;
	free(b.v);
	ft_print_debug("DEBUG: fbx_build_flat final count: %d vertices (%d tris)\n",
		b.vp, b.vp / 3);
}
