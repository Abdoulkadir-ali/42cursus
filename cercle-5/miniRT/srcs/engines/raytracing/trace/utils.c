/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	check_planes(const t_ray *ray, t_scene *sc, t_hit *hit, bool *any)
{
	t_hit	temp;
	size_t	i;

	if (!sc)
		return ;
	i = 0;
	while (i < sc->plane_count)
	{
		if (intersect_plane(ray, &sc->planes[i], &temp))
		{
			if (temp.t < hit->t)
			{
				*hit = temp;
				hit->ref.type = TYPE_PLANE;
				hit->ref.index = i;
				*any = true;
			}
		}
		i++;
	}
}

t_vec3	add_volumetrics(const t_ray *ray, t_scene *sc, double max_t)
{
	t_vec3	glow;
	size_t	i;
	double	t;
	double	d2;
	t_vec3	lv;

	glow = vec3(0, 0, 0);
	if (!sc || ray->depth > 0)
		return (glow);
	i = 0;
	while (i < sc->light_count)
	{
		lv = vec3_sub(sc->lights[i].transform.pos, ray->origin);
		t = vec3_dot(lv, ray->direction);
		if (t > 0 && t < max_t)
		{
			d2 = vec3_mag_sq(lv) - t * t;
			glow = vec3_add(glow, vec3_scale(sc->lights[i].rgb,
						sc->lights[i].brightness * 0.00004 / (d2 + 0.1)));
		}
		i++;
	}
	return (glow);
}
