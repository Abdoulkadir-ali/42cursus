/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:09:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:09:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	set_channel_path(t_anim_channel *chan, const char *p)
{
	chan->path = PATH_WEIGHTS;
	if (p && !strcmp(p, "translation"))
		chan->path = PATH_TRANSLATION;
	else if (p && !strcmp(p, "rotation"))
		chan->path = PATH_ROTATION;
	else if (p && !strcmp(p, "scale"))
		chan->path = PATH_SCALE;
}

void	assign_anim_data(t_animation *clip, t_json_value *anim_j)
{
	clip->name = ft_strdup(json_as_string(json_get(anim_j, "name")));
	if (!clip->name)
		clip->name = ft_strdup("(unnamed)");
	clip->current_time = 0.0;
	clip->max_time = 0.0;
}

void	update_max_time(t_animation *clip, t_anim_sampler *s)
{
	if (s->count > 0 && s->inputs[s->count - 1] > clip->max_time)
		clip->max_time = s->inputs[s->count - 1];
}
