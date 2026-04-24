/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:32:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

__attribute__((optimize("O3")))
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

__attribute__((optimize("O3")))
t_vec3	add_volumetrics(const t_ray *ray, t_scene *sc, double max_t)
{
	t_vec3	glow;
	size_t	i;
	float	t;
	float	d2;
	float	lvx;
	float	lvy;
	float	lvz;

	glow = vec3(0, 0, 0);
	if (!sc || ray->depth > 0)
		return (glow);
	i = 0;
	while (i < sc->light_count)
	{
		lvx = (float)(sc->lights[i].transform.pos.x - ray->origin.x);
		lvy = (float)(sc->lights[i].transform.pos.y - ray->origin.y);
		lvz = (float)(sc->lights[i].transform.pos.z - ray->origin.z);
		t = lvx * (float)ray->direction.x + lvy * (float)ray->direction.y
			+ lvz * (float)ray->direction.z;
		if (t > 0.0f && t < (float)max_t)
		{
			d2 = lvx * lvx + lvy * lvy + lvz * lvz - t * t;
			glow = vec3_add(glow, vec3_scale(sc->lights[i].rgb,
						sc->lights[i].brightness * 0.00004f / (d2 + 0.1f)));
		}
		i++;
	}
	return (glow);
}
