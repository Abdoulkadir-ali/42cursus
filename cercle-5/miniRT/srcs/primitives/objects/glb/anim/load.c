/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:32:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:12:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_channels(t_json_value *anim_json, t_animation *anim)
{
	t_json_value	*ch;
	t_json_value	*tgt;
	const char		*path;
	size_t			i;

	if (!json_get(anim_json, "channels"))
		return ;
	anim->channel_count = json_get(anim_json, "channels")->u.array.count;
		anim->channels = malloc(sizeof(t_anim_channel) * anim->channel_count);
	i = -1;
	while (++i < anim->channel_count)
	{
		ch = json_at(json_get(anim_json, "channels"), i);
		tgt = json_get(ch, "target");
		path = json_as_string(json_get(tgt, "path"));
		anim->channels[i].sampler_idx = json_get_size_t(ch, "sampler").i;
		anim->channels[i].node_idx = json_get_size_t(tgt, "node").i;
		anim->channels[i].path = PATH_WEIGHTS;
		if (path && !strcmp(path, "translation"))
			anim->channels[i].path = PATH_TRANSLATION;
		else if (path && !strcmp(path, "rotation"))
			anim->channels[i].path = PATH_ROTATION;
		else if (path && !strcmp(path, "scale"))
			anim->channels[i].path = PATH_SCALE;
	}
}

static void	assign_anim_data(t_animation *clip, t_json_value *anim_j)
{
	clip->name = ft_strdup(json_as_string(json_get(anim_j, "name")));
	clip->current_time = 0.0;
	clip->max_time = 0.0;
}

static void	update_max_time(t_animation *clip, t_anim_sampler *s)
{
	if (s->count > 0 && s->inputs[s->count - 1] > clip->max_time)
		clip->max_time = s->inputs[s->count - 1];
}

static void	load_all_samplers(t_json_value *j, char *bin, t_animation *clip,
				t_json_value *samplers)
{
	size_t	s;

	clip->sampler_count = samplers->u.array.count;
	clip->samplers = malloc(sizeof(t_anim_sampler) * clip->sampler_count);
	s = -1;
	while (++s < clip->sampler_count)
	{
		load_glb_sampler(j, bin, &clip->samplers[s], json_at(samplers, s));
		update_max_time(clip, &clip->samplers[s]);
	}
}

/**
 * Loads animations from a GLB JSON root into the scene's global clip pool.
 */
void	glb_load_animations(t_scene *scene, t_json_value *json, char *bin)
{
	t_animation		*clip;
	t_json_value	*anims;
	size_t			i;

	anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY)
		return ;
	glb_ensure_clip_capacity(scene, anims->u.array.count);
	i = -1;
	while (++i < anims->u.array.count)
	{
		clip = &scene->clips[scene->clip_count + i];
		assign_anim_data(clip, json_at(anims, i));
		load_all_samplers(json, bin, clip,
			json_get(json_at(anims, i), "samplers"));
		load_channels(json_at(anims, i), clip);
	}
	scene->clip_count += anims->u.array.count;
}
