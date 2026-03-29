/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_rect	unpack_rect(const t_primitive_array *p, int i)
{
	t_rect	re;

	ft_memset(&re, 0, sizeof(re));
	if (i < 0 || (size_t)i >= p->count)
		return (re);
	re.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	re.normal = vec3(p->ax[i], p->ay[i], p->az[i]);
	re.ex = p->ex[i];
	re.ey = p->ey[i];
	re.mat_idx = p->mat_ids[i];
	return (re);
}
