/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tris.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 04:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static int	fbx_read_poly(t_fbx_build *b, int *si)
{
	size_t	idx;
	int	vn;

	*si = b->ps;
	vn = 0;
	while ((size_t)b->ps < b->raw_c)
	{
		idx = b->raw[b->ps++];
		if ((long long)idx < 0)
			idx = idx ^ -1;
		b->v[vn++] = idx;
		if ((long long)b->raw[b->ps - 1] < 0)
			break ;
	}
	return (vn);
}

static void	fbx_emit_vertex(t_fbx_build *b, int v_index, int si, int offset)
{
	t_vertex	*v;

	v = &b->vertices[b->vp];
	v->pos = b->m->vertices[v_index].pos;
	if (b->n && b->nc > 0)
	{
		if (b->use_v_n)
			v->normal = b->n[v_index % b->nc];
		else
			v->normal = b->n[(si + offset) % b->nc];
	}
	if (b->u && b->uc > 0)
	{
		if (b->use_v_u)
			v->uv = b->u[v_index % b->uc];
		else
			v->uv = b->u[(si + offset) % b->uc];
	}
	b->vp++;
}

static void	fbx_emit_tris(t_fbx_build *b, int vn, int si)
{
	int	i;
	int	tri_idx;

	i = 1;
	while (i < vn - 1)
	{
		if (b->v[0] < b->vc && b->v[i] < b->vc && b->v[i + 1] < b->vc
			&& b->vp <= b->tc * 3 - 3)
		{
			tri_idx = b->vp / 3;
			fbx_emit_vertex(b, b->v[0], si, 0);
			fbx_emit_vertex(b, b->v[i], si, i);
			fbx_emit_vertex(b, b->v[i + 1], si, i + 1);
			b->triangles[tri_idx].v[0] = b->vp - 3;
			b->triangles[tri_idx].v[1] = b->vp - 2;
			b->triangles[tri_idx].v[2] = b->vp - 1;
		}
		i++;
	}
}

void	fbx_build_tris(t_fbx_build *b)
{
	int	vn;
	int	si;

	b->ps = 0;
	b->vp = 0;
	while ((size_t)b->ps < b->raw_c)
	{
		vn = fbx_read_poly(b, &si);
		fbx_emit_tris(b, vn, si);
	}
}
