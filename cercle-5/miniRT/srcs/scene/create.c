/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:14:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	*create_scene(const char *name)
{
	t_scene	*s;

	s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	s->name = name ? ft_strdup(name) : NULL;
	s->capacity = SCENE_INIT_CAP;
	s->count = 0;
	s->objects = ft_calloc(s->capacity, sizeof(t_object *));
	if (!s->objects)
	{
		free(s->name);
		free(s);
		return (NULL);
	}
	return (s);
}

bool	scene_add_object(t_scene *scene, t_object *obj)
{
	t_object	**new;
	size_t		ncap;

	if (!scene || !obj)
		return (false);
	if (scene->count == scene->capacity)
	{
		ncap = scene->capacity * 2;
		new = realloc(scene->objects, ncap * sizeof(*new));
		if (!new)
			return (false);
		memset(new + scene->capacity, 0, (ncap - scene->capacity)
			* sizeof(*new));
		scene->objects = new;
		scene->capacity = ncap;
	}
	scene->objects[scene->count++] = obj;
	return (true);
}
