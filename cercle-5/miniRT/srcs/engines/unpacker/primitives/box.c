/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_box	unpack_box(const t_primitive_array *p, int i)
{
	t_box	b;
	t_vec3	pos;
	t_vec3	ext;

	ft_memset(&b, 0, sizeof(b));
	if (i < 0 || (size_t)i >= p->count)
		return (b);
	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	ext = vec3(p->ex[i], p->ey[i], p->ez[i]);
	b.min = vec3_sub(pos, ext);
	b.max = vec3_add(pos, ext);
	b.mat_idx = p->mat_ids[i];
	return (b);
}
