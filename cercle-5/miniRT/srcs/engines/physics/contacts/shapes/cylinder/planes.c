/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:24:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

size_t	cylinder_vs_all_planes(t_contact_query *qu, t_col_pair *p)
{
	size_t	p_idx;

	p_idx = 0;
	while (p_idx < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		qu->count += gjk_vs_plane(p, &qu->engine->scene->planes[p_idx],
				&qu->contacts[qu->count]);
		p_idx++;
	}
	return (qu->count);
}
