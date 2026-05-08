/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:06:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex_cache.h"

t_cached_tex	*tex_cache_get(t_tex_cache *cache, const char *path)
{
	t_cached_tex	*curr;

	if (!cache || !path)
		return (NULL);
	curr = cache->head;
	while (curr)
	{
		if (ft_strcmp(curr->path, path) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	tex_cache_add(t_tex_cache *cache, const char *path, unsigned int *data,
		t_vec2s size)
{
	t_cached_tex	*new;

	if (!cache || !path || !data)
		return (0);
	new = malloc(sizeof(t_cached_tex));
	if (!new)
		return (0);
	new->path = ft_strdup(path);
	if (!new->path)
		return (free(new), 0);
	new->data = data;
	new->size = size;
	new->next = cache->head;
	cache->head = new;
	return (1);
}

void	tex_cache_free(t_tex_cache *cache)
{
	t_cached_tex	*curr;
	t_cached_tex	*next;

	if (!cache)
		return ;
	curr = cache->head;
	while (curr)
	{
		next = curr->next;
		free(curr->path);
		free(curr->data);
		free(curr);
		curr = next;
	}
	cache->head = NULL;
}
