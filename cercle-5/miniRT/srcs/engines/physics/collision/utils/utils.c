/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:10:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Utility for checking if a GJK shape is colliding with any of the
 * planes defined in the scene.
 */
int	gjk_vs_all_planes(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
		t_scene *s, t_contact *c, int count, int max)
{
	int	p;

	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += gjk_vs_plane(sa, ba, ta, &s->planes[p], &c[count]);
		p++;
	}
	return (count);
}
