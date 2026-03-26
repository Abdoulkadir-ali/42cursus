/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 18:19:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	load_sampler_data(t_json_value *json, char *bin, t_anim_sampler *s,
		t_json_value *sampler_json)
{
	t_accessor		acc;
	t_buffer_view	bv;
	int				in_idx;
	int				out_idx;
	const char		*interp = json_as_string(json_get(sampler_json,
						"interpolation"));
	t_json_value	*acc_json;
	const char		*type_str;
	int				num_comp;

	in_idx = json_get_int(sampler_json, "input");
	out_idx = json_get_int(sampler_json, "output");
	glb_parse_accessor(json, in_idx, &acc);
	s->count = acc.count;
	if (s->count <= 0)
		return ;
	s->inputs = malloc(sizeof(float) * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, s->inputs, sizeof(float),
		s->count, sizeof(float)});
	glb_parse_accessor(json, out_idx, &acc);
	s->outputs = malloc(sizeof(float) * 4 * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	acc_json = json_at(json_get(json, "accessors"), out_idx);
	type_str = json_as_string(json_get(acc_json, "type"));
	num_comp = 3;
	if (type_str && !strcmp(type_str, "VEC4"))
		num_comp = 4;
	if (type_str && !strcmp(type_str, "SCALAR"))
		num_comp = 1;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, s->outputs, sizeof(float)
		* num_comp, s->count, sizeof(float) * num_comp});
	s->method = INTERP_LINEAR;
	if (interp)
	{
		if (!strcmp(interp, "STEP"))
			s->method = INTERP_STEP;
		else if (!strcmp(interp, "CUBICSPLINE"))
			s->method = INTERP_CUBIC;
	}
}

static void	load_channels(t_json_value *anim_json, t_animation *anim)
{
	t_json_value	*chans;
	t_json_value	*ch;
	t_json_value	*tgt;
	const char		*path;

	chans = json_get(anim_json, "channels");
	if (!chans)
		return ;
	anim->channel_count = chans->array.count;
	anim->channels = malloc(sizeof(t_anim_channel) * anim->channel_count);
	for (int i = 0; i < anim->channel_count; i++)
	{
		ch = json_at(chans, i);
		tgt = json_get(ch, "target");
		path = json_as_string(json_get(tgt, "path"));
		anim->channels[i].sampler_idx = json_get_int(ch, "sampler");
		anim->channels[i].node_idx = json_get_int(tgt, "node");
		if (!path)
		{
			anim->channels[i].path = PATH_WEIGHTS;
			continue ;
		}
		if (!strcmp(path, "translation"))
			anim->channels[i].path = PATH_TRANSLATION;
		else if (!strcmp(path, "rotation"))
			anim->channels[i].path = PATH_ROTATION;
		else if (!strcmp(path, "scale"))
			anim->channels[i].path = PATH_SCALE;
		else
			anim->channels[i].path = PATH_WEIGHTS;
	}
}

static void	ensure_clip_capacity(t_scene *scene, int count)
{
	int			new_cap;
	t_animation	*new_clips;

	if (scene->clip_count + count <= scene->clip_cap)
		return ;
	new_cap = scene->clip_cap == 0 ? 4 : scene->clip_cap * 2;
	while (new_cap < scene->clip_count + count)
		new_cap *= 2;
	new_clips = malloc(sizeof(t_animation) * new_cap);
	if (scene->clips)
	{
		memcpy(new_clips, scene->clips, sizeof(t_animation)
			* scene->clip_count);
		free(scene->clips);
	}
	scene->clips = new_clips;
	scene->clip_cap = new_cap;
}

void	glb_load_animations(t_scene *scene, t_json_value *json, char *bin)
{
	t_json_value	*anims;
	int				count;
	t_animation		*clip;
	t_json_value	*anim_json;
	t_json_value	*samplers;
	float			last_time;

	fprintf(stderr, "GLB: Entering glb_load_animations...\n");
	anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY)
		return ;
	count = anims->array.count;
	ensure_clip_capacity(scene, count);
	for (int i = 0; i < count; i++)
	{
		clip = &scene->clips[scene->clip_count + i];
		anim_json = json_at(anims, i);
		clip->name = ft_strdup(json_as_string(json_get(anim_json, "name")));
		clip->current_time = 0.0;
		clip->max_time = 0.0;
		samplers = json_get(anim_json, "samplers");
		clip->sampler_count = samplers->array.count;
		clip->samplers = malloc(sizeof(t_anim_sampler) * clip->sampler_count);
		for (int s = 0; s < clip->sampler_count; s++)
		{
			load_sampler_data(json, bin, &clip->samplers[s], json_at(samplers,
					s));
			if (clip->samplers[s].count > 0)
			{
				last_time = clip->samplers[s].inputs[clip->samplers[s].count
					- 1];
				if (last_time > clip->max_time)
					clip->max_time = last_time;
			}
		}
		load_channels(anim_json, clip);
	}
	scene->clip_count += count;
	fprintf(stderr, "GLB: Loaded %d animations (Total: %d)\n", count,
		scene->clip_count);
}
