/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/27 14:56:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Bakes scene materials into a raytracer-optimized format.
 * This offloads the overhead of the editor/scene material structure
 * and prepares data for the hot shading path.
 */
void	bake_materials(t_rt_engine *rt, t_scene *scene)
{
	int	i;

	if (!scene || scene->mat_count <= 0)
		return ;
	if (rt->rt_materials)
		free(rt->rt_materials);
	rt->rt_materials = malloc(sizeof(t_rt_material) * scene->mat_count);
	if (!rt->rt_materials)
		return ;
	i = -1;
	while (++i < scene->mat_count)
	{
		rt->rt_materials[i].color = scene->materials[i].albedo_map.color_a;
		rt->rt_materials[i].specular = scene->materials[i].specular;
		rt->rt_materials[i].roughness = scene->materials[i].roughness;
		rt->rt_materials[i].metallic = scene->materials[i].metallic;
		rt->rt_materials[i].emission = scene->materials[i].emission;
		
		/* DOD: Load Albedo Texture */
		rt->rt_materials[i].albedo_tex_idx = -1;
		if (scene->materials[i].albedo_map.type == TEX_BITMAP &&
			scene->materials[i].albedo_map.path)
			rt->rt_materials[i].albedo_tex_idx = engine_pool_add_texture(rt, 
				scene->materials[i].albedo_map.path);

		/* DOD: Load Normal Map */
		rt->rt_materials[i].normal_map_idx = -1;
		if (scene->materials[i].bump_map.type == TEX_BUMP &&
			scene->materials[i].bump_map.path)
			rt->rt_materials[i].normal_map_idx = engine_pool_add_texture(rt, 
				scene->materials[i].bump_map.path);
	}
}
