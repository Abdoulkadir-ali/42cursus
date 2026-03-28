/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:54:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD Baking Bridge.
 * Extracts heavy Scene parameters and converts them into pure math constants
 * for the Raytracing Engine settings.
 */
void	raytrace_sync_settings(t_rt_engine *rt, t_scene *scene, int w, int h)
{
	rt->settings.width = w;
	rt->settings.height = h;
	rt->settings.inv_w = 1.0 / (double)w;
	rt->settings.inv_h = 1.0 / (double)h;
	rt->settings.aspect_ratio = (double)w / (double)h;
	
	/* Bake Camera FOV */
	rt->settings.fov = scene->camera.fov;
	rt->settings.fov_scale = tan(rt->settings.fov * 0.5 * M_PI / 180.0);
	
	/* Default Render Params */
	rt->settings.max_depth = 5;
	rt->settings.samples_per_pixel = 1;
	rt->settings.gamma = 2.2;
	rt->settings.shadow_bias = 0.001;
	rt->settings.void_color = scene->ambient.rgb;
}

void	raytrace_engine_sync(t_rt_engine *rt, t_scene *scene, int w, int h)
{
	if (!rt || !scene)
		return ;
	
	/* 1. Sync Settings (Bake Constants) */
	raytrace_sync_settings(rt, scene, w, h);
	
	/* 2. Bake Materials and Textures */
	bake_materials(rt, scene);
	
	/* 3. Pre-calculate Geometry state (Now handled on-the-fly or in BVH build) */
	
	/* 4. Link Geometry State */
	rt->scene = scene;
	
	/* 5. Rebuild Global BVH (DOD) */
	if (rt->bvh)
		bvh_destroy(rt->bvh);
	rt->bvh = bvh_build_global(scene);

	/* 6. Update internal version to track "dirty" state */
	rt->baked_version = scene->version;
}

/**
 * @brief Graceful Engine Cleanup.
 */
void	rt_engine_cleanup(t_rt_engine *rt)
{
	if (!rt)
		return ;
	engine_texture_pool_destroy(rt);
	if (rt->bvh)
		bvh_destroy(rt->bvh);
	if (rt->rt_materials)
		free(rt->rt_materials);
	if (rt->emissive_cache)
		free(rt->emissive_cache);
	rt->bvh = NULL;
	rt->rt_materials = NULL;
	rt->emissive_cache = NULL;
}
