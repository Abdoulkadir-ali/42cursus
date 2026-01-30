/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:13:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:13:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scenes	*create_scenes(void)
{
	t_scenes	*c;

	c = malloc(sizeof(*c));
	if (!c)
		return (NULL);
	c->capacity = SCENES_INIT_CAP;
	c->count = 0;
	c->scenes = ft_calloc(c->capacity, sizeof(t_scene));
	if (!c->scenes)
	{
		free(c);
		return (NULL);
	}
	return (c);
}

bool	scenes_add(t_scenes *scenes, t_scene *scene)
{
	t_scene	*new;
	size_t	ncap;

	if (!scenes || !scene)
		return (false);
	if (scenes->count == scenes->capacity)
	{
		ncap = scenes->capacity * 2;
		new = realloc(scenes->scenes, ncap * sizeof(*new));
		if (!new)
			return (false);
		memset(new + scenes->capacity, 0, (ncap - scenes->capacity)
			* sizeof(*new));
		scenes->scenes = new;
		scenes->capacity = ncap;
	}
	scenes->scenes[scenes->count++] = *scene;
	free(scene);
	return (true);
}

void	destroy_scenes(t_scenes *scenes)
{
	size_t	i;

	if (!scenes)
		return ;
	for (i = 0; i < scenes->count; i++)
		destroy_scene(&scenes->scenes[i]);
	free(scenes->scenes);
	free(scenes);
}
