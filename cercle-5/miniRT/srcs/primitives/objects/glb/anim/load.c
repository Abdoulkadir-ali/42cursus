/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:32:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:09:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_channels(t_json_value *anim_json, t_animation *anim)
{
	t_json_value	*ch;
	t_json_value	*tgt;
	const char		*path_s;
	size_t			i;

	if (!json_get(anim_json, "channels"))
		return ;
	anim->channel_count = json_get(anim_json, "channels")->u.array.count;
	anim->channels = malloc(sizeof(t_anim_channel) * anim->channel_count);
	i = 0;
	while (i < anim->channel_count)
	{
		ch = json_at(json_get(anim_json, "channels"), i);
		tgt = json_get(ch, "target");
		path_s = json_as_string(json_get(tgt, "path"));
		anim->channels[i].sampler_idx = json_get_size_t(ch, "sampler").i;
		anim->channels[i].node_idx = json_get_size_t(tgt, "node").i;
		set_channel_path(&anim->channels[i], path_s);
		i++;
	}
}

static void	load_all_samplers(t_json_value *j, char *bin, t_animation *clip,
				t_json_value *samplers)
{
	size_t	s;

	clip->sampler_count = samplers->u.array.count;
	clip->samplers = malloc(sizeof(t_anim_sampler) * clip->sampler_count);
	s = 0;
	while (s < clip->sampler_count)
	{
		load_glb_sampler(j, bin, &clip->samplers[s], json_at(samplers, s));
		update_max_time(clip, &clip->samplers[s]);
		s++;
	}
}

static void	glb_load_clip(t_scene *scene, t_json_value *json, char *bin,
		size_t i)
{
	t_animation		*clip;
	t_json_value	*anims;
	t_json_value	*samplers;

	anims = json_get(json, "animations");
	clip = &scene->clips[scene->clip_count + i];
	assign_anim_data(clip, json_at(anims, i));
	samplers = json_get(json_at(anims, i), "samplers");
	ft_print_debug("GLB: Anim %zu: '%s'\n", i + 1, clip->name);
	load_all_samplers(json, bin, clip, samplers);
	load_channels(json_at(anims, i), clip);
}

void	glb_load_animations(t_scene *scene, t_json_value *json, char *bin)
{
	t_json_value	*anims;
	size_t			i;

	anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY)
		return ;
	glb_ensure_clip_capacity(scene, anims->u.array.count);
	i = 0;
	while (i < anims->u.array.count)
	{
		glb_load_clip(scene, json, bin, i);
		i++;
	}
	scene->clip_count += anims->u.array.count;
}
