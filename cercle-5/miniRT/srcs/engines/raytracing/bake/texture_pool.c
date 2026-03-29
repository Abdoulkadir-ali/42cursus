/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:59:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Loads a single texture into the engine's raw pixel pool.
 */
int	engine_pool_add_texture(t_rt_engine *rt, const char *path)
{
	int				w, h, channels;
	unsigned char	*pixels;
	size_t			idx;
	size_t			*count_ptr;
	size_t			*cap_ptr;
	int				i;

	if (!path)
		return (-1);
	i = -1;
	while (++i < rt->texture_count)
	{
		if (rt->texture_names && rt->texture_names[i]
			&& strcmp(rt->texture_names[i], path) == 0)
		{
			DBG_TRACE_MSG(DBG_CH_TEXTURE,
				"tex_pool: CACHED %s idx=%d\n", path, i);
			return (i);
		}
	}
	pixels = stbi_load(path, &w, &h, &channels, 4); /* Force RGBA */
	if (!pixels)
	{
		DBG_ERR_MSG(DBG_CH_TEXTURE,
			"tex_pool: stbi_load FAIL %s\n", path);
		return (-1);
	}
	count_ptr = (size_t *)&rt->texture_count;
	cap_ptr = (size_t *)&rt->texture_cap;
	idx = rt->texture_count;
	if (!DYNARRAY_ENSURE_INT(&rt->texture_pool, count_ptr,
			cap_ptr, sizeof(unsigned char *)))
		return (-1);
	rt->texture_count--;
	if (!DYNARRAY_ENSURE_INT(&rt->texture_dims, count_ptr,
			cap_ptr, sizeof(t_vec2i)))
		return (-1);
	rt->texture_count--;
	if (!DYNARRAY_ENSURE_INT(&rt->texture_names, count_ptr,
			cap_ptr, sizeof(char *)))
		return (-1);
	rt->texture_pool[idx] = pixels;
	rt->texture_dims[idx] = vec2i(w, h);
	rt->texture_names[idx] = strdup(path);
	DBG_INFO_MSG(DBG_CH_TEXTURE,
		"tex_pool: LOAD %s %dx%d idx=%zu\n", path, w, h, idx);
	return ((int)idx);
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
	{
		stbi_image_free(rt->texture_pool[i]);
		if (rt->texture_names && rt->texture_names[i])
			free(rt->texture_names[i]);
	}
	free(rt->texture_pool);
	free(rt->texture_dims);
	if (rt->texture_names)
		free(rt->texture_names);
	rt->texture_pool = NULL;
	rt->texture_dims = NULL;
	rt->texture_names = NULL;
	rt->texture_count = 0;
	rt->texture_cap = 0;
}
