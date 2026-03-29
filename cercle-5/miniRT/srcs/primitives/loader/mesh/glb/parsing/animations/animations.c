/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 09:40:22 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 11:18:37 by abdoali          ###   ########.fr       */
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
 * @brief Parses individual animation sampler data into a pre-allocated pool.
 */
static void	glb_parse_sampler(t_json_value *json, char *bin, t_anim_sampler *s, 
		t_json_value *sj, float **pool_ptr)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	const char		*interp;

	glb_parse_accessor(json, json_get_int(sj, "input"), &acc);
	s->count = acc.count;
	s->inputs = *pool_ptr;
	*pool_ptr += s->count;
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data(bin, &acc, &bv, s->inputs);
	glb_parse_accessor(json, json_get_int(sj, "output"), &acc);
	s->outputs = *pool_ptr;
	*pool_ptr += 5 * s->count; /* Guard for cubicspline (3) or rot (4) */
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
 * @brief Logic for loading animation samplers using a unified pool.
 */
static void	load_samplers(t_json_value *json, char *bin, t_animation *clip)
{
	size_t			i;
	float			time;
	size_t			total;
	t_json_value	*smps;
	float			*pool;
	t_glb_accessor	acc;

	smps = json_get(json, "samplers");
	clip->sampler_count = (int)smps->array.count;
	clip->samplers = ft_calloc(clip->sampler_count, sizeof(t_anim_sampler));
	total = 0; i = 0;
	while (i < (size_t)clip->sampler_count)
	{
		glb_parse_accessor(json, json_get_int(json_at(smps, i), "input"), &acc);
		total += acc.count;
		glb_parse_accessor(json, json_get_int(json_at(smps, i), "output"), &acc);
		total += 5 * acc.count;
		i++;
	}
	clip->anim_pool = malloc(sizeof(float) * total);
	pool = clip->anim_pool;
	i = 0;
	while (i < (size_t)clip->sampler_count)
	{
		glb_parse_sampler(json, bin, &clip->samplers[i], json_at(smps, i), &pool);
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

void	glb_load_skeleton_impl(t_mesh_asset *mesh, t_json_value *json, char *bin, int idx)
{
	t_json_value *skin = json_at(json_get(json, "skins"), idx);
	t_json_value *joints;
	t_json_value *nodes = json_get(json, "nodes");
	t_glb_accessor acc; t_glb_buffer_view bv;
	int i, node_idx, node_count;
	int *node_to_joint; int *child_to_parent;

	if (!skin) return;
	joints = json_get(skin, "joints");
	if (!joints) return;
	mesh->bone_count = (int)joints->array.count;
	mesh->skeleton = ft_calloc(mesh->bone_count, sizeof(t_bone));
	mesh->bone_matrices = ft_calloc(mesh->bone_count, sizeof(t_mat4));
	glb_parse_accessor(json, json_get_int(skin, "inverseBindMatrices"), &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data(bin, &acc, &bv, mesh->bone_matrices); /* Use scratch area */
	node_count = (int)nodes->array.count;
	node_to_joint = malloc(sizeof(int) * node_count);
	child_to_parent = malloc(sizeof(int) * node_count);
	i = 0; while (i < node_count) { node_to_joint[i] = -1; child_to_parent[i] = -1; i++; }
	i = 0; while (i < mesh->bone_count) {
		node_idx = json_get_int(json_at(joints, i), NULL);
		if (node_idx >= 0 && node_idx < node_count) node_to_joint[node_idx] = i; 
		i++; }
	i = 0; while (i < node_count) {
		t_json_value *children = json_get(json_at(nodes, i), "children");
		size_t j = 0; while (children && j < children->array.count) {
			int cid = json_get_int(json_at(children, j++), NULL);
			if (cid >= 0 && cid < node_count) child_to_parent[cid] = i; }
		i++; }
	i = 0;
	while (i < mesh->bone_count)
	{
		node_idx = mesh->skeleton[i].node_idx = json_get_int(json_at(joints, i), NULL);
		mesh->skeleton[i].inv_bind_pose = mesh->bone_matrices[i];
		mesh->skeleton[i].trs.scale = vec3(1,1,1);
		mesh->skeleton[i].parent = -1;
		if (node_idx >= 0 && node_idx < node_count && child_to_parent[node_idx] != -1)
			mesh->skeleton[i].parent = node_to_joint[child_to_parent[node_idx]];
		i++;
	}
	free(node_to_joint); free(child_to_parent);
}
