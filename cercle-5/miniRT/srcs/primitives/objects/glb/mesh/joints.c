/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:54:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:16:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	set_joint_val(t_mesh *m, t_extract_attr *attr, size_t i, size_t k)
{
	unsigned short	*us;
	unsigned char	*uc;

	if (attr->comp_type == GLB_TYPE_UNSIGNED_SHORT)
	{
		us = (unsigned short *)attr->tmp;
		m->weights[i].bone_indices[k] = us[i * 4 + k];
	}
	else
	{
		uc = (unsigned char *)attr->tmp;
		m->weights[i].bone_indices[k] = uc[i * 4 + k];
	}
}

static void	init_joint_attr(t_extract_attr *at, t_accessor *acc)
{
	at->comp_type = acc->component_type;
	at->c_sz = 1;
	if (at->comp_type == GLB_TYPE_UNSIGNED_SHORT)
		at->c_sz = 2;
}

void	load_joints(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_extract_attr	at;
	t_accessor		acc;
	t_buffer_view	bv;
	size_t			i;
	size_t			k;

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	init_joint_attr(&at, &acc);
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
			set_joint_val(m, &at, i, k);
	}
	free(at.tmp);
}
