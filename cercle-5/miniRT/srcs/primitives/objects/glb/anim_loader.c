/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:20:00 by abdoali          ###   ########.fr       */
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
	if (type_str && !ft_strcmp(type_str, "VEC4"))
		num_comp = 4;
	if (type_str && !ft_strcmp(type_str, "SCALAR"))
		num_comp = 1;
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, s->outputs, sizeof(float)
		* num_comp, s->count, sizeof(float) * num_comp});
	s->method = INTERP_LINEAR;
	if (interp)
	{
		if (!ft_strcmp(interp, "STEP"))
			s->method = INTERP_STEP;
		else if (!ft_strcmp(interp, "CUBICSPLINE"))
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
		if (!ft_strcmp(path, "translation"))
			anim->channels[i].path = PATH_TRANSLATION;
		else if (!ft_strcmp(path, "rotation"))
			anim->channels[i].path = PATH_ROTATION;
		else if (!ft_strcmp(path, "scale"))
			anim->channels[i].path = PATH_SCALE;
		else
			anim->channels[i].path = PATH_WEIGHTS;
	}
}

t_animation	*glb_extract_animations(t_json_value *json, char *bin, int *out_count)
{
	t_json_value	*anims;
	int				count;
	t_animation		*clips;
	t_json_value	*anim_json;
	t_json_value	*samplers;
	float			last_time;

	anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY)
	{
		*out_count = 0;
		return (NULL);
	}
	count = anims->array.count;
	*out_count = count;
	clips = ft_calloc(count, sizeof(t_animation));
	if (!clips)
		return (NULL);
	for (int i = 0; i < count; i++)
	{
		anim_json = json_at(anims, i);
		clips[i].name = ft_strdup(json_as_string(json_get(anim_json, "name")));
		clips[i].current_time = 0.0;
		clips[i].max_time = 0.0;
		samplers = json_get(anim_json, "samplers");
		clips[i].sampler_count = samplers->array.count;
		clips[i].samplers = malloc(sizeof(t_anim_sampler) * clips[i].sampler_count);
		for (int s = 0; s < clips[i].sampler_count; s++)
		{
			load_sampler_data(json, bin, &clips[i].samplers[s], json_at(samplers, s));
			if (clips[i].samplers[s].count > 0)
			{
				last_time = clips[i].samplers[s].inputs[clips[i].samplers[s].count - 1];
				if (last_time > clips[i].max_time)
					clips[i].max_time = last_time;
			}
		}
		load_channels(anim_json, &clips[i]);
	}
	return (clips);
}
