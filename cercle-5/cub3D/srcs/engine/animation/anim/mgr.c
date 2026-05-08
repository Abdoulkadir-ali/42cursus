/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 02:40:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_anim_clip	*find_in_cache(t_cached_clip *cache, const char *path)
{
	while (cache)
	{
		if (ft_strcmp(cache->path, path) == 0)
			return (&cache->clip);
		cache = cache->next;
	}
	return (NULL);
}

static t_cached_clip	*create_cached_node(t_window *win, const char *path,
		t_world *world)
{
	t_cached_clip	*new_node;

	new_node = ft_calloc(1, sizeof(t_cached_clip));
	if (!new_node)
		return (NULL);
	new_node->path = ft_strdup(path);
	if (!new_node->path || !load_anim_clip(&new_node->clip, win, path, world))
	{
		free(new_node->path);
		anim_free_clip(&new_node->clip);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_anim_clip	*anim_get_cached_clip(t_world *world, t_window *win,
		const char *path, t_app *app)
{
	t_anim_clip		*existing;
	t_cached_clip	*new_node;

	if (!world || !path)
		return (NULL);
	existing = find_in_cache(world->anim_mgr.cache, path);
	if (existing)
		return (existing);
	new_node = create_cached_node(win, path, world);
	if (!new_node)
	{
		if (app)
			safe_exit("could not load animation: %s", app, 1, path);
		return (NULL);
	}
	new_node->next = world->anim_mgr.cache;
	world->anim_mgr.cache = new_node;
	return (&new_node->clip);
}

void	anim_mgr_free(t_world *world)
{
	t_cached_clip	*curr;
	t_cached_clip	*next;

	if (!world)
		return ;
	curr = world->anim_mgr.cache;
	while (curr)
	{
		next = curr->next;
		free(curr->path);
		anim_free_clip(&curr->clip);
		free(curr);
		curr = next;
	}
	world->anim_mgr.cache = NULL;
	tex_cache_free(&world->tex_cache);
	if (world->door_grid)
	{
		free(world->door_grid);
		world->door_grid = NULL;
	}
}
