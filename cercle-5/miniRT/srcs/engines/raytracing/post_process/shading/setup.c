/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:04:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	apply_thermal_blend(t_shading *sha)
{
	t_vec3	bb;
	double	blend;

	if (sha->mat.temperature <= 0.0)
		return ;
	bb = rt_kelvin_to_rgb(sha->mat.temperature);
	blend = 1.0 - exp(-sha->mat.temperature / 600.0);
	sha->albedo.x = sha->albedo.x * (1.0 - blend) + bb.x * blend;
	sha->albedo.y = sha->albedo.y * (1.0 - blend) + bb.y * blend;
	sha->albedo.z = sha->albedo.z * (1.0 - blend) + bb.z * blend;
}

void	setup_shading(t_shading *sha, t_hit *hit, t_scene *scene,
		const t_bvh *bvh)
{
	float	r;

	sha->hit = hit;
	sha->scene = scene;
	sha->bvh = bvh;
	sha->opts = scene->opts;
	sha->frame_idx = sha->ray->frame_idx;
	get_material(sha);
	sha->albedo = sample_texture(&sha->mat.albedo_map, hit->u, hit->v);
	if (sha->mat.roughness_map.type == TEX_BITMAP)
		sha->mat.roughness = sample_texture(&sha->mat.roughness_map,
				hit->u, hit->v).x / 255.0;
	if (sha->mat.metallic_map.type == TEX_BITMAP)
		sha->mat.metallic = sample_texture(&sha->mat.metallic_map,
				hit->u, hit->v).x / 255.0;
	r = 1.0f - (float)sha->mat.roughness;
	sha->mat.shininess = (double)r * r * r * r * 200.0 + 2.0;
	sha->mat.specular = sha->mat.specular * (1.0 - sha->mat.metallic * 0.5)
		+ sha->mat.metallic * 0.9;
	apply_bump(sha);
	apply_thermal_blend(sha);
}
