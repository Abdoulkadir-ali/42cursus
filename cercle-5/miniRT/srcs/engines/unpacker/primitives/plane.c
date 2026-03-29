/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_plane	unpack_plane(const t_primitive_array *p, int i)
{
	t_plane	pl;

	ft_memset(&pl, 0, sizeof(pl));
	if (i < 0 || (size_t)i >= p->count)
		return (pl);
	pl.point = vec3(p->px[i], p->py[i], p->pz[i]);
	pl.normal = vec3(p->ax[i], p->ay[i], p->az[i]);
	pl.mat_idx = p->mat_ids[i];
	return (pl);
}
