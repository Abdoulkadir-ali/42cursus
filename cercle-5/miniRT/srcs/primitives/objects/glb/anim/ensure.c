/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ensure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:39:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:01:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Dynamically resizes the scene's global animation clip pool to ensure
 * there is enough space for 'count' new clips.
 */
void	glb_ensure_clip_capacity(t_scene *scene, int count)
{
	size_t			new_cap;
	t_animation		*new_clips;

	if (scene->clip_count + count <= scene->clip_cap)
		return ;
	if (scene->clip_cap == 0)
		new_cap = 4;
	else
		new_cap = scene->clip_cap * 2;
	while (new_cap < scene->clip_count + count)
		new_cap *= 2;
	new_clips = malloc(sizeof(t_animation) * new_cap);
	if (scene->clips)
	{
		ft_memcpy(new_clips, scene->clips,
			sizeof(t_animation) * scene->clip_count);
		free(scene->clips);
	}
	scene->clips = new_clips;
	scene->clip_cap = new_cap;
}
