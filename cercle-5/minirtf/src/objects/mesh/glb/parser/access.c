/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:21:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"

int	glb_bv_get(const t_glb *g, int idx, size_t *off, size_t *len, int *stride)
{
	const char	*bv;
	const char	*v;

	bv = json_arr_get(json_obj_find(g->json, g->jend, "bufferViews"), g->jend,
			idx);
	if (!bv)
		return (-1);
	*off = 0;
	*stride = 0;
	v = json_obj_find(bv, g->jend, "byteOffset");
	if (v)
		*off = (size_t)json_int(v, g->jend);
	v = json_obj_find(bv, g->jend, "byteLength");
	if (!v)
		return (-1);
	*len = (size_t)json_int(v, g->jend);
	v = json_obj_find(bv, g->jend, "byteStride");
	if (v)
		*stride = (int)json_int(v, g->jend);
	return (0);
}

static int	type_nelems(const char *p, const char *end)
{
	if (!p || *p != '"')
		return (1);
	if (json_streq(p, end, "SCALAR"))
		return (1);
	if (json_streq(p, end, "VEC2"))
		return (2);
	if (json_streq(p, end, "VEC3"))
		return (3);
	if (json_streq(p, end, "VEC4"))
		return (4);
	if (json_streq(p, end, "MAT4"))
		return (16);
	return (1);
}

static int	comp_size(int comp_type)
{
	if (comp_type == GLT_BYTE || comp_type == GLT_UBYTE)
		return (1);
	if (comp_type == GLT_SHORT || comp_type == GLT_USHORT)
		return (2);
	return (4);
}

int	glb_acc_get(const t_glb *g, int idx, t_glb_acc *o)
{
	const char	*a;
	const char	*v;
	size_t		bv_off;
	size_t		bv_len;
	size_t		acc_off;
	int			bv_idx;
	int			bv_stride;

	a = json_arr_get(json_obj_find(g->json, g->jend, "accessors"), g->jend,
			idx);
	if (!a)
		return (-1);
	v = json_obj_find(a, g->jend, "bufferView");
	if (!v)
		return (-1);
	bv_idx = (int)json_int(v, g->jend);
	if (glb_bv_get(g, bv_idx, &bv_off, &bv_len, &bv_stride) < 0)
		return (-1);
	acc_off = 0;
	v = json_obj_find(a, g->jend, "byteOffset");
	if (v)
		acc_off = (size_t)json_int(v, g->jend);
	v = json_obj_find(a, g->jend, "componentType");
	if (!v)
		return (-1);
	o->comp_type = (int)json_int(v, g->jend);
	v = json_obj_find(a, g->jend, "count");
	if (!v)
		return (-1);
	o->count = (int)json_int(v, g->jend);
	o->nelems = type_nelems(json_obj_find(a, g->jend, "type"), g->jend);
	o->normalized = 0;
	v = json_obj_find(a, g->jend, "normalized");
	if (v && (*v == 't' || *v == 'T'))
		o->normalized = 1;
	o->stride = bv_stride;
	if (o->stride <= 0)
		o->stride = comp_size(o->comp_type) * o->nelems;
	o->data = g->bin + bv_off + acc_off;
	return (0);
}
