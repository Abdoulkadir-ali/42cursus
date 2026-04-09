/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:15:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static void	fbx_init_build(t_fbx_build *b, t_mesh *m, t_fbx_flat_params *p)
{
	ft_memset(b, 0, sizeof(*b));
	b->m = m;
	b->raw = p->raw;
	b->rv.x = p->rv.x;
	b->n = p->n;
	b->nu.x = p->nu.x;
	b->u = p->u;
	b->nu.y = p->nu.y;
	b->rv.y = p->rv.y;
	b->tc = fbx_count_tris(b->raw, b->rv.x);
	b->m->tri_count = b->tc;
}

static bool	fbx_alloc_buffers(t_fbx_build *b)
{
	b->vertices = ft_calloc(b->tc * 3, sizeof(t_vertex));
	b->triangles = ft_calloc(b->tc, sizeof(t_triangle));
	b->v = malloc(sizeof(*b->v) * (b->rv.y + 1));
	if (!b->vertices || !b->triangles || !b->v)
		return (false);
	return (true);
}

static void	fbx_set_usage(t_fbx_build *b)
{
	if (b->n && b->nu.x > 0 && b->nu.x < b->tc * 3)
		b->use_v_n = true;
	if (b->u && b->nu.y > 0 && b->nu.y < b->tc * 3)
		b->use_v_u = true;
}

bool	fbx_setup_build(t_fbx_build *b, t_mesh *m, t_fbx_flat_params *p)
{
	fbx_init_build(b, m, p);
	if (b->tc <= 0)
		return (false);
	if (!fbx_alloc_buffers(b))
	{
		fbx_free_build(b);
		return (false);
	}
	fbx_set_usage(b);
	return (true);
}
