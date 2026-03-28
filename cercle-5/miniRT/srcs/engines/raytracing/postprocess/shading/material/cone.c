/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:03:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	get_cone_mat(t_shading *sha)
{
	t_hit	*h;

	h = sha->hit;
	if (h->ref.index >= 0 && h->ref.index < (int)sha->rt->scene->primitives.count)
		return (sha->rt->scene->primitives.mat_ids[h->ref.index]);
	return (0);
}
