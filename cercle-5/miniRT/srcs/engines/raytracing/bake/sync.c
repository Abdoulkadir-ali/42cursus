/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:28:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "debug.h"

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
	bool	settings_dirty;
	bool	scene_dirty;

	if (!rt || !scene)
		return ;
	settings_dirty = (rt->settings.width != w || rt->settings.height != h);
	scene_dirty = (__atomic_load_n(&rt->baked_version, __ATOMIC_ACQUIRE)
			!= scene->version);
	DBG_INFO_MSG(DBG_CH_BVH,
		"rt_sync: settings_dirty=%d scene_dirty=%d v=%u mats=%zu prims=%zu\n",
		settings_dirty, scene_dirty, scene->version, scene->mat_count,
		scene->primitives.count);
	if (settings_dirty)
		raytrace_sync_settings(rt, scene, w, h);
	if (!scene_dirty)
		return ;
	if (!bake_materials(rt, scene))
	{
		DBG_WARN_MSG(DBG_CH_BVH, "rt_sync: bake_materials FAIL mats=%zu\n",
			scene->mat_count);
		return ;
	}
	DBG_INFO_MSG(DBG_CH_BVH, "rt_sync: bake_materials OK mats=%zu\n",
		scene->mat_count);
	rt->scene = scene;
	if (rt->bvh)
		bvh_destroy(rt->bvh);
	DBG_INFO_MSG(DBG_CH_BVH, "rt_sync: bvh_build_global start prims=%zu\n",
		scene->primitives.count);
	rt->bvh = bvh_build_global(scene);
	DBG_INFO_MSG(DBG_CH_BVH, "rt_sync: bvh=%p\n", (void *)rt->bvh);
	pthread_mutex_lock(&rt->bake_lock);
	rt->emissive_cache = scene->emissive_cache;
	rt->emissive_n = (int)scene->emissive_count;
	pthread_mutex_unlock(&rt->bake_lock);
	__atomic_store_n(&rt->baked_version, scene->version, __ATOMIC_RELEASE);
	DBG_INFO_MSG(DBG_CH_BVH, "rt_sync: DONE baked_v=%u emissive=%d\n",
		scene->version, rt->emissive_n);
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
	rt->emissive_cache = NULL;
	rt->bvh = NULL;
	rt->rt_materials = NULL;
	rt->emissive_cache = NULL;
}
