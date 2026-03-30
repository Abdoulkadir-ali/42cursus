/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Main entry point for ray-cone intersection.
*/
bool	intersect_cone(const t_ray *ray, t_cone *cone, t_hit *hit)
{
	double	t;

	t = DBL_MAX;
	if (check_cone_body(ray, cone, &t, cone->transform.scale.y))
	{
		if (t < hit->t)
		{
			fill_hit_record(hit, ray, cone, t);
			return (true);
		}
	}
	return (false);
}
