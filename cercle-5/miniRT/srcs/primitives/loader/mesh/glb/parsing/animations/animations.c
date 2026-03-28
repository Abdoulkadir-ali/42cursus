/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 09:40:22 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:27:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Context for mapping animation paths to stay under variable limits.
 */
static void	map_path(t_anim_channel *chan, const char *path)
{
	chan->path = PATH_WEIGHTS;
	if (path == NULL)
		return ;
	if (ft_strcmp(path, "translation") == 0)
		chan->path = PATH_TRANSLATION;
	else if (ft_strcmp(path, "rotation") == 0)
		chan->path = PATH_ROTATION;
	else if (ft_strcmp(path, "scale") == 0)
		chan->path = PATH_SCALE;
}

/**
 * @brief Parses individual animation sampler data from binary chunks.
 */
void	glb_parse_sampler(t_json_value *json, char *bin, t_anim_sampler *s, 
		t_json_value *sj)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	const char		*interp;

	glb_parse_accessor(json, json_get_int(sj, "input"), &acc);
	s->count = acc.count;
	s->inputs = malloc(sizeof(float) * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data(bin, &acc, &bv, s->inputs);
	glb_parse_accessor(json, json_get_int(sj, "output"), &acc);
	s->outputs = malloc(sizeof(float) * 4 * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data(bin, &acc, &bv, s->outputs);
	interp = json_as_string(json_get(sj, "interpolation"));
	s->method = INTERP_LINEAR;
	if (interp != NULL && ft_strcmp(interp, "STEP") == 0)
		s->method = INTERP_STEP;
	else if (interp != NULL && ft_strcmp(interp, "CUBICSPLINE") == 0)
		s->method = INTERP_CUBIC;
}

/**
 * @brief Logic for loading individual channels without for loops.
 */
static void	load_chan_list(t_json_value *chans, t_animation *anim)
{
	size_t			i;
	t_json_value	*ch;
	t_json_value	*tgt;

	anim->channel_count = (int)chans->array.count;
	anim->channels = malloc(sizeof(t_anim_channel) * anim->channel_count);
	if (anim->channels == NULL)
		return ;
	i = 0;
	while (i < (size_t)anim->channel_count)
	{
		ch = json_at(chans, i);
		tgt = json_get(ch, "target");
		anim->channels[i].sampler_idx = json_get_int(ch, "sampler");
		anim->channels[i].node_idx = json_get_int(tgt, "node");
		map_path(&anim->channels[i], json_as_string(json_get(tgt, "path")));
		i++;
	}
}

/**
 * @brief Logic for loading animation samplers.
 */
static void	load_samplers(t_json_value *json, char *bin, t_animation *clip)
{
	size_t			i;
	float			time;
	t_json_value	*smps;

	smps = json_get(json, "samplers");
	clip->sampler_count = (int)smps->array.count;
	clip->samplers = malloc(sizeof(t_anim_sampler) * clip->sampler_count);
	i = 0;
	while (i < (size_t)clip->sampler_count)
	{
		glb_parse_sampler(json, bin, &clip->samplers[i], json_at(smps, i));
		if (clip->samplers[i].count > 0)
		{
			time = clip->samplers[i].inputs[clip->samplers[i].count - 1];
			if (time > clip->max_time)
				clip->max_time = time;
		}
		i++;
	}
}

/**
 * @brief Entry point for GLB animation extraction.
 */
t_animation *glb_extract_animations(t_json_value *json, char *bin, int *out_count)
{
	t_json_value	*anims;
	t_animation		*clips;
	size_t			i;

	anims = json_get(json, "animations");
	if (anims == NULL || anims->type != JSON_ARRAY)
	{
		*out_count = 0;
		return (NULL);
	}
	*out_count = (int)anims->array.count;
	clips = ft_calloc(*out_count, sizeof(t_animation));
	i = 0;
	while (i < (size_t)*out_count)
	{
		clips[i].name = ft_strdup(json_as_string(json_get(json_at(anims, i),
						"name")));
		load_samplers(json, bin, &clips[i]);
		load_chan_list(json_get(json_at(anims, i), "channels"), &clips[i]);
		i++;
	}
	return (clips);
}

static int	find_parent_node(t_json_value *nodes, int target_node)
{
	size_t			i;
	size_t			j;
	t_json_value	*n;
	t_json_value	*children;

	i = 0;
	while (i < nodes->array.count)
	{
		n = json_at(nodes, i);
		children = json_get(n, "children");
		if (children && children->type == JSON_ARRAY)
		{
			j = 0;
			while (j < children->array.count)
			{
				if (json_get_int(json_at(children, j), NULL) == target_node)
					return ((int)i);
				j++;
			}
		}
		i++;
	}
	return (-1);
}

void	glb_load_skeleton_impl(t_mesh *mesh, t_json_value *json, char *bin, int idx)
{
	t_json_value	*skins = json_get(json, "skins");
	t_json_value	*skin = json_at(skins, idx);
	t_json_value	*joints;
	t_glb_accessor	acc;
	t_glb_buffer_view bv;
	t_mat4 *ibms;
	t_json_value *nodes;
	int i, j, node_idx, parent_node;

	if (!skin) return;
	joints = json_get(skin, "joints");
	mesh->bone_count = (int)joints->array.count;
	mesh->skeleton = ft_calloc(mesh->bone_count, sizeof(t_bone));
	mesh->bone_matrices = ft_calloc(mesh->bone_count, sizeof(t_mat4));

	glb_parse_accessor(json, json_get_int(skin, "inverseBindMatrices"), &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	ibms = malloc(sizeof(t_mat4) * mesh->bone_count);
	glb_extract_data(bin, &acc, &bv, ibms);

	nodes = json_get(json, "nodes");
	i = 0;
	while (i < mesh->bone_count)
	{
		node_idx = json_get_int(json_at(joints, i), NULL);
		mesh->skeleton[i].node_idx = node_idx;
		mesh->skeleton[i].inv_bind_pose = ibms[i];
		mesh->skeleton[i].trs.scale = vec3(1,1,1);
		
		parent_node = find_parent_node(nodes, node_idx);
		mesh->skeleton[i].parent = -1;
		if (parent_node != -1)
		{
			j = 0;
			while (j < mesh->bone_count)
			{
				if (json_get_int(json_at(joints, j), NULL) == parent_node)
				{
					mesh->skeleton[i].parent = j;
					break;
				}
				j++;
			}
		}
		i++;
	}
	free(ibms);
}
