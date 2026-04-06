/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 15:19:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static size_t	fbx_count_tris(size_t *raw, size_t raw_c)
{
	size_t	ps;
	int		vn;
	int		idx;
	int		tc;

	ft_print_debug("[COUNT_TRIS] raw=%p raw_c=%zu raw[0]=%zu\n",
		(void *)raw, raw_c, raw_c > 0 ? raw[0] : 0);
	ps = 0;
	tc = 0;
	while (ps < raw_c)
	{
		vn = 0;
		while (ps < raw_c)
		{
			idx = raw[ps++];
			vn++;
			if (idx < 0)
				break ;
		}
		if (vn >= 3)
			tc += (vn - 2);
	}
	ft_print_debug("[COUNT_TRIS] result tc=%d\n", tc);
	return (tc);
}

static void	fbx_init_build(t_fbx_build *b, t_mesh *m, t_fbx_flat_params *p)
{
	ft_memset(b, 0, sizeof(*b));
	b->m = m;
	b->raw = p->raw;
	b->raw_c = p->raw_c;
	b->n = p->n;
	b->nc = p->nc;
	b->u = p->u;
	b->uc = p->uc;
	b->vc = p->vc;
	b->tc = fbx_count_tris(b->raw, b->raw_c);
	b->m->tri_count = b->tc;
}

static bool	fbx_alloc_buffers(t_fbx_build *b)
{
	b->vertices = ft_calloc(b->tc * 3, sizeof(t_vertex));
	b->triangles = ft_calloc(b->tc, sizeof(t_triangle));
	b->v = malloc(sizeof(*b->v) * (b->raw_c + 1));
	if (!b->vertices || !b->triangles || !b->v)
		return (false);
	return (true);
}

static void	fbx_set_usage(t_fbx_build *b)
{
	if (b->n && b->nc > 0 && b->nc < b->tc * 3)
		b->use_v_n = 1;
	if (b->u && b->uc > 0 && b->uc < b->tc * 3)
		b->use_v_u = 1;
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
