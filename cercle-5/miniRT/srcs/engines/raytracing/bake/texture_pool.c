/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:56:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "raytracing.h"

/**
 * @brief Simple linear search for texture path in the current engine pool.
 * Returns the index or -1 if not found.
 */
static int	find_texture_in_pool(t_rt_engine *rt, const char *path)
{
	int	i;

	if (!path || !*path)
		return (-1);
	/* Note: Currently surface metadata doesn't store path in Engine context.
	 * We'd need to store paths temporarily during baking to avoid re-loading.
	 * For now, this is a skeleton for the DOD pipeline.
	 */
	return (-1); 
}

/**
 * @brief Loads a single texture into the engine's raw pixel pool.
 */
int	engine_pool_add_texture(t_rt_engine *rt, const char *path)
{
	int				w, h, channels;
	unsigned char	*pixels;
	int				idx;

	pixels = stbi_load(path, &w, &h, &channels, 4); /* Force RGBA */
	if (!pixels)
		return (-1);
	
	idx = rt->texture_count;
	/* Use existing dynamic array helpers */
	if (!DYNARRAY_ENSURE_INT(&rt->texture_pool, &rt->texture_count,
			&rt->texture_cap, sizeof(unsigned char *)))
		return (-1);
	rt->texture_count--; /* Keep count in sync with second allocation */
	
	if (!DYNARRAY_ENSURE_INT(&rt->texture_dims, &rt->texture_count,
			&rt->texture_cap, sizeof(t_vec2i)))
		return (-1);
	
	rt->texture_pool[idx] = pixels;
	rt->texture_dims[idx] = vec2i(w, h);
	return (idx);
}

/**
 * @brief Cleans up the raw pixel storage.
 */
void	engine_texture_pool_destroy(t_rt_engine *rt)
{
	int	i;

	if (!rt->texture_pool)
		return ;
	i = -1;
	while (++i < rt->texture_count)
		stbi_image_free(rt->texture_pool[i]);
	free(rt->texture_pool);
	free(rt->texture_dims);
	rt->texture_pool = NULL;
	rt->texture_dims = NULL;
	rt->texture_count = 0;
	rt->texture_cap = 0;
}
