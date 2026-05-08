/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:57:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 14:34:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	anim_init_clip(t_anim_clip *clip)
{
	if (!clip)
		return (0);
	clip->frames = malloc(sizeof(unsigned int *) * 8);
	if (!clip->frames)
		return (0);
	clip->frame_capacity = 8;
	clip->frame_count = 0;
	clip->original_fps = 0;
	clip->frame_duration_us = 0;
	return (1);
}

void	anim_free_clip(t_anim_clip *clip)
{
	size_t	i;

	if (!clip || !clip->frames)
		return ;
	i = 0;
	while (i < clip->frame_count)
	{
		free(clip->frames[i]);
		clip->frames[i] = NULL;
		i++;
	}
	free(clip->frames);
	clip->frames = NULL;
	clip->frame_count = 0;
	clip->frame_capacity = 0;
}

void	anim_free(t_anim *anim)
{
	if (!anim)
		return ;
	if (anim->punch_texture.data)
		free(anim->punch_texture.data);
	anim->punch_texture.data = NULL;
}
