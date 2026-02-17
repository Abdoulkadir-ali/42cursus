/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

static void	load_sampler_data(t_json_value *json, char *bin, t_anim_sampler *s,
		t_json_value *sampler_json)
{
	t_accessor		acc;
	t_buffer_view	bv;
	int				in_idx = json_get_int(sampler_json, "input");
	int				out_idx = json_get_int(sampler_json, "output");
	const char		*interp = json_as_string(json_get(sampler_json, "interpolation"));

	/* Inputs (Times) - Scalar Float */
	glb_parse_accessor(json, in_idx, &acc);
	s->count = acc.count;
	/* Validate count > 0 */
	if (s->count <= 0) return ;
	
	s->inputs = malloc(sizeof(float) * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, s->inputs,
		sizeof(float), s->count, sizeof(float)});

	/* Outputs (Keys) - Vec3/Vec4 Float */
	glb_parse_accessor(json, out_idx, &acc);
	/* Assuming Vec3 or Vec4. Stride might vary. We store as floats.
	   Wait, we don't know if Vec3 or Vec4 here?
	   We do via 'type' string in accessor, but glb_parse_accessor doesn't return that string easily.
	   However, Rotation is VEC4 (4 floats), Trans/Scale is VEC3 (3 floats).
	   We will store everything as flat float array and interpret later based on Channel Path.
	   Wait, if Path is Rot, we read 4 floats per key. If Trans, 3 floats.
	   
	   BUT, one sampler might be used by multiple channels?
	   Yes.
	   So the sampler data size depends on the accessor type.
	   
	   Let's check accessor.type "VEC3" or "VEC4".
	   glb_parse_accessor doesn't parse 'type' string into enum.
	   But it reads 'count'. Buffer size?
	   We can infer stride from accessor or just allocate enough.
	   Let's allocate 4 floats per key to be safe (Vec4 max).
	*/
	
	s->outputs = malloc(sizeof(float) * 4 * s->count);
	
	/* Re-parse buffer view for output */
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	
	/* Extract. Stride depends on element size. VEC3=12, VEC4=16. */
	/* We rely on glb_extract_data using accessor stride. */
	/* But we need to know how many floats to copy per element? */
	/* Extract ctx takes 'stride' of destination. */
	
	/* Hack: We don't know if it's 3 or 4 floats. */
	/* Let's peek the accessor JSON 'type' manually? */
	t_json_value *acc_json = json_at(json_get(json, "accessors"), out_idx);
	const char *type_str = json_as_string(json_get(acc_json, "type"));
	int num_comp = 3;
	if (type_str && !strcmp(type_str, "VEC4")) num_comp = 4;
	if (type_str && !strcmp(type_str, "SCALAR")) num_comp = 1;

	glb_extract_data((t_extract_ctx){bin, &acc, &bv, s->outputs,
		sizeof(float) * num_comp, s->count, sizeof(float) * num_comp});
	
	/* If we allocated 4 but only read 3, the 4th is garbage. That's fine if we only read 3 later. */

	/* Interpolation */
	s->method = INTERP_LINEAR;
	if (interp)
	{
		if (!strcmp(interp, "STEP")) s->method = INTERP_STEP;
		else if (!strcmp(interp, "CUBICSPLINE")) s->method = INTERP_CUBIC;
	}
}

static void load_channels(t_json_value *anim_json, t_animation *anim)
{
	t_json_value *chans = json_get(anim_json, "channels");
	if (!chans) return;
	
	anim->channel_count = chans->u.array.count;
	anim->channels = malloc(sizeof(t_anim_channel) * anim->channel_count);
	
	for (int i = 0; i < anim->channel_count; i++)
	{
		t_json_value *ch = json_at(chans, i);
		t_json_value *tgt = json_get(ch, "target");
		
		anim->channels[i].sampler_idx = json_get_int(ch, "sampler");
		anim->channels[i].node_idx = json_get_int(tgt, "node");
		
		const char *path = json_as_string(json_get(tgt, "path"));
		if (!strcmp(path, "translation")) anim->channels[i].path = PATH_TRANSLATION;
		else if (!strcmp(path, "rotation")) anim->channels[i].path = PATH_ROTATION;
		else if (!strcmp(path, "scale")) anim->channels[i].path = PATH_SCALE;
		else anim->channels[i].path = PATH_WEIGHTS;
	}
}

static void ensure_clip_capacity(t_scene *scene, int count)
{
	if (scene->clip_count + count <= scene->clip_cap) return;
	
	int new_cap = scene->clip_cap == 0 ? 4 : scene->clip_cap * 2;
	while (new_cap < scene->clip_count + count) new_cap *= 2;
	
	t_animation *new_clips = malloc(sizeof(t_animation) * new_cap);
	/* Init new memory if debug needed, or just standard */
	if (scene->clips)
	{
		memcpy(new_clips, scene->clips, sizeof(t_animation) * scene->clip_count);
		free(scene->clips);
	}
	scene->clips = new_clips;
	scene->clip_cap = new_cap;
}

void	glb_load_animations(t_scene *scene, t_json_value *json, char *bin)
{
	fprintf(stderr, "GLB: Entering glb_load_animations...\n");
	t_json_value *anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY) return;

	int count = anims->u.array.count;
	ensure_clip_capacity(scene, count);
	
	/* Load each animation */
	for (int i = 0; i < count; i++)
	{
		t_animation *clip = &scene->clips[scene->clip_count + i];
		t_json_value *anim_json = json_at(anims, i);
		
		clip->name = ft_strdup(json_as_string(json_get(anim_json, "name")));
		clip->current_time = 0.0;
		clip->max_time = 0.0;
		
		/* Load Samplers */
		t_json_value *samplers = json_get(anim_json, "samplers");
		clip->sampler_count = samplers->u.array.count;
		clip->samplers = malloc(sizeof(t_anim_sampler) * clip->sampler_count);
		
		for (int s = 0; s < clip->sampler_count; s++)
		{
			load_sampler_data(json, bin, &clip->samplers[s], json_at(samplers, s));
			/* Update Max Time */
			if (clip->samplers[s].count > 0)
			{
				float last_time = clip->samplers[s].inputs[clip->samplers[s].count - 1];
				if (last_time > clip->max_time) clip->max_time = last_time;
			}
		}
		
		load_channels(anim_json, clip);
	}
	scene->clip_count += count;
	fprintf(stderr, "GLB: Loaded %d animations (Total: %d)\n", count, scene->clip_count);
}
