/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Computes the final shaded color for a hit point.
*/
static t_vec3	clamp_color(t_vec3 color)
{
	if (color.x < 0)
		color.x = 0;
	if (color.y < 0)
		color.y = 0;
	if (color.z < 0)
		color.z = 0;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

/*
** Scales and clamps a color value.
*/
t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = (obj.x / 255.0) * (light.x / 255.0) * intensity * 255.0;
	f.y = (obj.y / 255.0) * (light.y / 255.0) * intensity * 255.0;
	f.z = (obj.z / 255.0) * (light.z / 255.0) * intensity * 255.0;
	return (f);
}

t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray)
{
	t_shading_ctx	ctx;
	t_vec3			total;
	int				i;

	ctx.hit = hit;
	ctx.scene = scene;
	ctx.bvh = bvh;
	ctx.ray = ray;
	get_material(&ctx);
	ctx.albedo = sample_texture(&ctx.mat.albedo_map, hit->u, hit->v);
	apply_bump(&ctx);
	total = pixel_color(ctx.albedo, scene->ambient.rgb,
			scene->ambient.brightness);
	i = 0;
	while (i < scene->light_count)
	{
		total = vec3_add(total, calc_light(&ctx, scene->lights[i]));
		i++;
	}
	return (clamp_color(total));
}
