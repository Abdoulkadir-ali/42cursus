/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:23:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static unsigned int	read_uint_at(const unsigned char *p, int comp_type)
{
	unsigned short	u16;
	unsigned int	u32;

	if (comp_type == GLT_UBYTE || comp_type == GLT_BYTE)
		return ((unsigned int)p[0]);
	if (comp_type == GLT_USHORT || comp_type == GLT_SHORT)
	{
		memcpy(&u16, p, 2);
		return ((unsigned int)u16);
	}
	memcpy(&u32, p, 4);
	return (u32);
}

static float	read_float_at(const unsigned char *p, int comp_type,
		int normalized)
{
	float			f;
	signed char		i8;
	short			i16;

	if (comp_type == GLT_FLOAT)
	{
		memcpy(&f, p, 4);
		return (f);
	}
	if (comp_type == GLT_UBYTE)
		return (normalized ? p[0] / 255.0f : (float)p[0]);
	if (comp_type == GLT_USHORT)
	{
		memcpy(&i16, p, 2);
		return (normalized ? (unsigned short)i16 / 65535.0f
			: (float)(unsigned short)i16);
	}
	if (comp_type == GLT_BYTE)
	{
		i8 = (signed char)p[0];
		return (normalized ? fmaxf(i8 / 127.0f, -1.0f) : (float)i8);
	}
	if (comp_type == GLT_SHORT)
	{
		memcpy(&i16, p, 2);
		return (normalized ? fmaxf(i16 / 32767.0f, -1.0f) : (float)i16);
	}
	return (0.0f);
}

static int	comp_size(int t)
{
	if (t == GLT_BYTE || t == GLT_UBYTE)
		return (1);
	if (t == GLT_SHORT || t == GLT_USHORT)
		return (2);
	return (4);
}

float	*glb_read_float(const t_glb *g, int acc_idx, int *out_count,
		int *out_nelems)
{
	t_glb_acc	a;
	float		*out;
	int			i;
	int			j;
	int			cs;

	if (acc_idx < 0 || glb_acc_get(g, acc_idx, &a) < 0)
		return (NULL);
	out = (float *)malloc(sizeof(float) * a.count * a.nelems);
	if (!out)
		return (NULL);
	cs = comp_size(a.comp_type);
	i = -1;
	while (++i < a.count)
	{
		j = -1;
		while (++j < a.nelems)
			out[i * a.nelems + j] = read_float_at(
					a.data + (size_t)i * a.stride + (size_t)j * cs,
					a.comp_type, a.normalized);
	}
	*out_count = a.count;
	if (out_nelems)
		*out_nelems = a.nelems;
	return (out);
}

unsigned int	*glb_read_uint(const t_glb *g, int acc_idx, int *out_count,
		int *out_nelems)
{
	t_glb_acc	a;
	unsigned int	*out;
	int				i;
	int				j;
	int				cs;

	if (acc_idx < 0 || glb_acc_get(g, acc_idx, &a) < 0)
		return (NULL);
	out = (unsigned int *)malloc(sizeof(unsigned int) * a.count * a.nelems);
	if (!out)
		return (NULL);
	cs = comp_size(a.comp_type);
	i = -1;
	while (++i < a.count)
	{
		j = -1;
		while (++j < a.nelems)
			out[i * a.nelems + j] = read_uint_at(
					a.data + (size_t)i * a.stride + (size_t)j * cs,
					a.comp_type);
	}
	*out_count = a.count;
	if (out_nelems)
		*out_nelems = a.nelems;
	return (out);
}
