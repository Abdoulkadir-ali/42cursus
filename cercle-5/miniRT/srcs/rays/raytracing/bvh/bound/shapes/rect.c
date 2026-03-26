/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:07:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_aabb	rect_aabb(t_rect *rc)
{
	t_aabb	bbox;
	int		i;

	bbox = aabb_create_empty();
	i = -1;
	while (++i < 4)
		aabb_expand_point(&bbox, rc->v[i]);
	aabb_expand_eps(&bbox, 1e-4);
	return (bbox);
}

