/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

static void	glb_log_anim(const char *fmt, ...)
{
	va_list	args;
	FILE	*f;

	f = fopen("debug_glb.txt", "a");
	if (f)
	{
		va_start(args, fmt);
		vfprintf(f, fmt, args);
		va_end(args);
		fclose(f);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

static void inspect_channel(t_json_value *chan, int idx)
{
	t_json_value *target = json_get(chan, "target");
	int node = json_get_int(target, "node");
	const char *path = json_as_string(json_get(target, "path"));
	int sampler = json_get_int(chan, "sampler");

	glb_log_anim("    Channel %d: Target Node %d -> Path '%s' (Sampler %d)\n",
		idx, node, path ? path : "UNKNOWN", sampler);
}

void glb_inspect_animations(t_json_value *json)
{
	t_json_value *anims = json_get(json, "animations");
	if (!anims || anims->type != JSON_ARRAY)
	{
		glb_log_anim("GLB: No 'animations' array found.\n");
		return;
	}

	size_t count = anims->array.count;
	glb_log_anim("GLB: Found %zu animations.\n", count);

	for (size_t i = 0; i < count; i++)
	{
		t_json_value *anim = json_at(anims, i);
		const char *name = json_as_string(json_get(anim, "name"));
		glb_log_anim("GLB: Animation %zu: '%s'\n", i, name ? name : "Unnamed");

		t_json_value *channels = json_get(anim, "channels");
		if (channels && channels->type == JSON_ARRAY)
		{
			glb_log_anim("  Channels: %zu\n", channels->array.count);
			for (size_t j = 0; j < channels->array.count; j++)
			{
				inspect_channel(json_at(channels, j), j);
			}
		}

		t_json_value *samplers = json_get(anim, "samplers");
		if (samplers && samplers->type == JSON_ARRAY)
		{
			glb_log_anim("  Samplers: %zu\n", samplers->array.count);
		}
	}
}

void glb_inspect_skins(t_json_value *json)
{
	t_json_value *skins = json_get(json, "skins");
	if (!skins || skins->type != JSON_ARRAY)
	{
		glb_log_anim("GLB: No 'skins' array found.\n");
		return;
	}

	size_t count = skins->array.count;
	glb_log_anim("GLB: Found %zu skins.\n", count);

	for (size_t i = 0; i < count; i++)
	{
		t_json_value *skin = json_at(skins, i);
		t_json_value *joints = json_get(skin, "joints");
		int skeleton = json_get_int(skin, "skeleton");
		int ibm = json_get_int(skin, "inverseBindMatrices");

		glb_log_anim("GLB: Skin %zu: Skeleton Root Node: %d, IBM Accessor: %d\n",
			i, skeleton, ibm);
		
		if (joints && joints->type == JSON_ARRAY)
		{
			glb_log_anim("  Joints (%zu): [", joints->array.count);
			for (size_t j = 0; j < joints->array.count; j++)
			{
				glb_log_anim("%d%s", (int)json_as_number(json_at(joints, j)),
					j < joints->array.count - 1 ? ", " : "");
			}
			glb_log_anim("]\n");
		}
	}
}

void glb_inspect_nodes(t_json_value *json)
{
	t_json_value *nodes = json_get(json, "nodes");
	if (!nodes || nodes->type != JSON_ARRAY)
	{
		glb_log_anim("GLB: No 'nodes' array found.\n");
		return;
	}

	size_t count = nodes->array.count;
	glb_log_anim("GLB: Found %zu nodes.\n", count);

	for (size_t i = 0; i < count; i++)
	{
		t_json_value *node = json_at(nodes, i);
		t_json_value *children = json_get(node, "children");
		glb_log_anim("GLB: Node %zu: ", i);
		if (children && children->type == JSON_ARRAY)
		{
			glb_log_anim("Children [");
			for (size_t j = 0; j < children->array.count; j++)
			{
				glb_log_anim("%d%s", (int)json_as_number(json_at(children, j)),
					j < children->array.count - 1 ? ", " : "");
			}
			glb_log_anim("], ");
		}
		if (json_get(node, "mesh")) glb_log_anim("Has MESH, ");
		if (json_get(node, "skin")) glb_log_anim("Has SKIN, ");
		if (json_get(node, "translation")) glb_log_anim("Has POS, ");
		if (json_get(node, "rotation")) glb_log_anim("Has ROT, ");
		if (json_get(node, "scale")) glb_log_anim("Has SCL, ");
		glb_log_anim("\n");
	}
}
