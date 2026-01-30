/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:19:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:19:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	destroy_scene(t_scene *scene)
{
	size_t	i;

	if (!scene)
		return ;
	for (i = 0; i < scene->count; i++)
		destroy_object(scene->objects[i]);
	free(scene->objects);
	free(scene->name);
	free(scene);
}

void	print_scene(t_scene *scene)
{
	size_t	i;

	if (!scene)
		return ;
	printf("Scene: %s (objects: %zu)\n",
		scene->name ? scene->name : "(unnamed)", scene->count);
	for (i = 0; i < scene->count; i++)
	{
		printf("--- object %zu:\n", i);
		print_object(scene->objects[i]);
	}
}
