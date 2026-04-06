/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 17:19:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static size_t	fbx_read_poly(t_fbx_build *b, size_t *si)
{
	int		idx;
	size_t	vn;

	*si = b->cur.y;
	vn = 0;
	while (b->cur.y < b->rv.x)
	{
		idx = b->raw[b->cur.y++];
		if (idx < 0)
			idx = idx ^ -1;
		b->v[vn++] = (size_t)idx;
		if (b->raw[b->cur.y - 1] < 0)
			break ;
	}
	return (vn);
}

static void	fbx_emit_vertex(t_fbx_build *b, size_t v_index,
				size_t si, size_t offset)
{
	t_vertex	*v;

	v = &b->vertices[b->cur.x];
	v->pos = b->m->vertices[v_index].pos;
	if (b->n && b->nu.x > 0)
	{
		if (b->use_v_n)
			v->normal = b->n[v_index % b->nu.x];
		else
			v->normal = b->n[(si + offset) % b->nu.x];
	}
	if (b->u && b->nu.y > 0)
	{
		if (b->use_v_u)
			v->uv = b->u[v_index % b->nu.y];
		else
			v->uv = b->u[(si + offset) % b->nu.y];
	}
	b->cur.x++;
}

static void	fbx_emit_tris(t_fbx_build *b, size_t vn, size_t si)
{
	size_t	i;
	size_t	tri_idx;

	if (vn < 3)
		return ;
	i = 1;
	while (i < vn - 1)
	{
		if (b->v[0] < b->rv.y && b->v[i] < b->rv.y && b->v[i + 1] < b->rv.y
			&& b->cur.x <= b->tc * 3 - 3)
		{
			tri_idx = b->cur.x / 3;
			fbx_emit_vertex(b, b->v[0], si, 0);
			fbx_emit_vertex(b, b->v[i], si, i);
			fbx_emit_vertex(b, b->v[i + 1], si, i + 1);
			b->triangles[tri_idx].v[0] = b->cur.x - 3;
			b->triangles[tri_idx].v[1] = b->cur.x - 2;
			b->triangles[tri_idx].v[2] = b->cur.x - 1;
		}
		i++;
	}
}

void	fbx_build_tris(t_fbx_build *b)
{
	size_t	vn;
	size_t	si;

	b->cur.y = 0;
	b->cur.x = 0;
	while (b->cur.y < b->rv.x)
	{
		vn = fbx_read_poly(b, &si);
		fbx_emit_tris(b, vn, si);
	}
}
