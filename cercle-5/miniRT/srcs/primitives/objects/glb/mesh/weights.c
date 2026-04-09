/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:16:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:16:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	set_weight_val(t_mesh *m, t_extract_attr *at, size_t i, size_t k)
{
	float			*f;
	unsigned short	*us;
	unsigned char	*uc;

	if (at->comp_type == GLB_TYPE_FLOAT)
	{
		f = (float *)at->tmp;
		m->weights[i].weights[k] = f[i * 4 + k];
	}
	else if (at->comp_type == GLB_TYPE_UNSIGNED_SHORT)
	{
		us = (unsigned short *)at->tmp;
		m->weights[i].weights[k] = us[i * 4 + k] / GLB_MAX_U16;
	}
	else
	{
		uc = (unsigned char *)at->tmp;
		m->weights[i].weights[k] = uc[i * 4 + k] / GLB_MAX_U8;
	}
}

static void	init_weight_attr(t_extract_attr *at, t_accessor *acc)
{
	at->comp_type = acc->component_type;
	at->c_sz = 4;
	if (at->comp_type == GLB_TYPE_UNSIGNED_SHORT)
		at->c_sz = 2;
	else if (at->comp_type == GLB_TYPE_UNSIGNED_BYTE)
		at->c_sz = 1;
}

void	load_skin_weights(t_json_value *json, char *bin, t_mesh *m,
				int acc_idx)
{
	t_extract_attr	at;
	t_accessor		acc;
	t_buffer_view	bv;
	size_t			i;
	size_t			k;

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	init_weight_attr(&at, &acc);
	at.tmp = ft_calloc(at.c_sz * 4, acc.count);
	if (!at.tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, at.tmp,
		at.c_sz * 4, at.c_sz * 4, at.c_sz * 4, acc.count});
	i = -1;
	while (++i < acc.count)
	{
		k = -1;
		while (++k < 4)
			set_weight_val(m, &at, i, k);
	}
	free(at.tmp);
}
