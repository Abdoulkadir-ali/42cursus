/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"
#include <stdio.h>
#include <stdarg.h>

void	glb_init_bone_colliders(t_mesh *mesh);

static t_mat4 quat_to_mat4(double x, double y, double z, double w)
{
	t_mat4 m = mat4_identity();
	double xx = x * x; double yy = y * y; double zz = z * z;
	double xy = x * y; double xz = x * z; double yz = y * z;
	double wx = w * x; double wy = w * y; double wz = w * z;

	m.m[0][0] = 1.0 - 2.0 * (yy + zz);
	m.m[0][1] = 2.0 * (xy + wz);
	m.m[0][2] = 2.0 * (xz - wy);

	m.m[1][0] = 2.0 * (xy - wz);
	m.m[1][1] = 1.0 - 2.0 * (xx + zz);
	m.m[1][2] = 2.0 * (yz + wx);

	m.m[2][0] = 2.0 * (xz + wy);
	m.m[2][1] = 2.0 * (yz - wx);
	m.m[2][2] = 1.0 - 2.0 * (xx + yy);

	return m;
}

static void	load_ibms(t_json_value *json, char *bin, int acc_idx, t_mat4 *dst, int count)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	int				i;

	glb_parse_accessor(json, acc_idx, &acc);
	if (acc.count != count)
		return ; // Warning
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	
	tmp = malloc(sizeof(float) * 16 * count);
	if (!tmp) return ;
	
	glb_extract_data((t_extract_ctx){bin, &acc, &bv, tmp,
		sizeof(float) * 16, count, sizeof(float) * 16});
	
	for (i = 0; i < count; i++)
	{
		for (int r = 0; r < 4; r++)
			for (int c = 0; c < 4; c++)
				dst[i].m[c][r] = tmp[i * 16 + c * 4 + r];
	}
	free(tmp);
}

/* Helper because maths.h doesn't seem to expose complete basic API sometimes */
static t_mat4	make_transform(t_vec3 t, t_vec3 r_quat, double scale[3])
{
	t_mat4 mt = mat4_translation(t);
	t_mat4 mr = quat_to_mat4(r_quat.x, r_quat.y, r_quat.z, r_quat.w);
	t_mat4 ms = mat4_scaling(vec3(scale[0], scale[1], scale[2]));
	
	// S * R * T
	return mat4_mul(ms, mat4_mul(mr, mt));
}

static void	glb_log(const char *fmt, ...)
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

void	glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin,
		int extra_count)
{
	glb_log("GLB: Attempting to load skeleton...\n");
	t_json_value	*skins = json_get(json, "skins");
	t_json_value	*nodes = json_get(json, "nodes");

	if (!skins || !nodes) {
		glb_log("GLB: Skeleton Load Aborted: 'skins' or 'nodes' missing.\n");
		return ;
	}
	
	/* Assume Skin 0 for now */
	t_json_value *skin = json_at(skins, 0);
	if (!skin) return ;

	t_json_value *joints = json_get(skin, "joints");
	if (!joints) return;
	int count = joints->u.array.count;
	
	glb_log("GLB: Building skeleton with %d bones + %d extra (IBM acc: %d)...\n", 
		count, extra_count, (int)json_get_int(skin, "inverseBindMatrices"));

	mesh->skeleton = malloc(sizeof(t_bone) * (count + extra_count));
	mesh->bone_matrices = malloc(sizeof(t_mat4) * (count + extra_count));
	mesh->bone_count = count;
	
	/* IBMs */
	int ibm_acc = json_get_int(skin, "inverseBindMatrices");
	t_mat4 *ibms = malloc(sizeof(t_mat4) * count);
	load_ibms(json, bin, ibm_acc, ibms, count);

	/* Map Node Index -> Skeleton Index */
	int *node_map = malloc(sizeof(int) * 65536); // Hacky safe size
	for (int i=0; i<65536; i++) node_map[i] = -1;

	for (int i = 0; i < count; i++)
	{
		int node_idx = (int)json_as_number(json_at(joints, i));
		node_map[node_idx] = i;
		
		mesh->skeleton[i].node_idx = node_idx;
		mesh->skeleton[i].parent = -1;
		mesh->skeleton[i].inv_bind_pose = ibms[i];
		mesh->bone_matrices[i] = mat4_identity(); // Init runtime state

		/* Parse Local Transform */
		t_json_value *node = json_at(nodes, node_idx);
		
		t_vec3 t = vec3(0,0,0);
		t_vec3 r = {0,0,0,1}; // Quat
		double s[3] = {1,1,1};

		t_json_value *jt = json_get(node, "translation");
		if (jt) t = vec3(json_as_number(json_at(jt, 0)), json_as_number(json_at(jt, 1)), json_as_number(json_at(jt, 2)));

		t_json_value *jr = json_get(node, "rotation");
		if (jr) {
			r.x = json_as_number(json_at(jr, 0));
			r.y = json_as_number(json_at(jr, 1));
			r.z = json_as_number(json_at(jr, 2));
			r.w = json_as_number(json_at(jr, 3));
		}

		t_json_value *js = json_get(node, "scale");
		if (js) {
			s[0] = json_as_number(json_at(js, 0));
			s[1] = json_as_number(json_at(js, 1));
			s[2] = json_as_number(json_at(js, 2));
		}

		mesh->skeleton[i].trs.pos = t;
		mesh->skeleton[i].trs.rot = r;
		mesh->skeleton[i].trs.scale = vec3(s[0], s[1], s[2]);
		mesh->skeleton[i].local_transform = make_transform(t, r, s);
		mesh->skeleton[i].bind_pose = mesh->skeleton[i].local_transform; // Default
	}
	free(ibms);

	/* Pass 2: Linking Parents */
	for (int i = 0; i < count; i++)
	{
		int node_idx = (int)json_as_number(json_at(joints, i));
		t_json_value *node = json_at(nodes, node_idx);
		t_json_value *children = json_get(node, "children");
		
		if (children)
		{
			for (size_t c = 0; c < children->u.array.count; c++)
			{
				int child_node = (int)json_as_number(json_at(children, c));
				if (child_node < 65536)
				{
					int child_skel_idx = node_map[child_node];
					if (child_skel_idx != -1)
						mesh->skeleton[child_skel_idx].parent = i;
				}
			}
		}
	}
	free(node_map);
	glb_log("GLB: Skeleton built successfully with %d bones.\n", count);
	
	/* Initialize Bone Physics (Stage 8) */
	glb_init_bone_colliders(mesh);
}

/**
 * @brief Auto-generates capsule colliders for skeletal segments.
 * For every bone with a valid parent, it creates a physics brick connecting them.
 */
void	glb_init_bone_colliders(t_mesh *mesh)
{
	int		i;
	t_bone	*b;
	double	dist;

	if (!mesh->skeleton || mesh->bone_count == 0)
		return ;
	mesh->phys.is_compound = true;
	mesh->phys.sub_count = 0;
	i = 0;
	while (i < mesh->bone_count && mesh->phys.sub_count < 32)
	{
		b = &mesh->skeleton[i];
		/* Use parent-child segments as capsules */
		if (b->parent != -1)
		{
			dist = vec3_mag(b->trs.pos);
			if (dist > 0.05) /* Skip tiny bones (fingers etc) */
			{
				b->has_collider = true;
				b->sub_idx = mesh->phys.sub_count++;
				mesh->phys.sub_shapes[b->sub_idx].type = TYPE_PHYS_CAPSULE;
				mesh->phys.sub_shapes[b->sub_idx].radius = 0.1; /* Default */
				/* Offset is midpoint of bone segment */
				mesh->phys.sub_shapes[b->sub_idx].offset = vec3_scale(b->trs.pos, 0.5);
			}
		}
		i++;
	}
	/* Tier 2 & 3 initialization */
	update_compound(&mesh->phys);
}

/* Count non-joint GLTF nodes that reference a mesh — these need extra bone
** slots so the rigid transform can follow an animated parent joint. */
int	glb_count_extra_anim_nodes(t_json_value *json)
{
	t_json_value	*skins;
	t_json_value	*joints;
	t_json_value	*nodes_arr;
	int				*is_joint;
	int				extra;
	int				node_idx;
	int				nc;
	int				i;

	skins = json_get(json, "skins");
	if (!skins)
		return (0);
	joints = json_get(json_at(skins, 0), "joints");
	if (!joints)
		return (0);
	nodes_arr = json_get(json, "nodes");
	if (!nodes_arr)
		return (0);
	nc = (int)nodes_arr->u.array.count;
	is_joint = ft_calloc(65536, sizeof(int));
	if (!is_joint)
		return (0);
	i = 0;
	while (i < (int)joints->u.array.count)
	{
		node_idx = (int)json_as_number(json_at(joints, i));
		if (node_idx >= 0 && node_idx < 65536)
			is_joint[node_idx] = 1;
		i++;
	}
	extra = 0;
	i = 0;
	while (i < nc && i < 65536)
	{
		if (!is_joint[i] && (int)json_get_int(json_at(nodes_arr, i), "mesh") >= 0)
			extra++;
		i++;
	}
	free(is_joint);
	return (extra);
}

/* For each non-joint GLTF node that references a mesh, add a bone slot and
** link it to its nearest joint ancestor so the rigid transform inherits the
** parent bone's animated global_transform automatically. */
static void	fill_bone_trs(t_bone *bone, t_json_value *node)
{
	t_json_value	*jt;
	t_json_value	*jr;
	t_json_value	*js;
	t_vec3			t;
	t_vec3			r;
	double			s[3];

	t = vec3(0, 0, 0);
	r.x = 0; r.y = 0; r.z = 0; r.w = 1;
	s[0] = 1; s[1] = 1; s[2] = 1;
	jt = json_get(node, "translation");
	if (jt)
		t = vec3(json_as_number(json_at(jt, 0)),
			json_as_number(json_at(jt, 1)),
			json_as_number(json_at(jt, 2)));
	jr = json_get(node, "rotation");
	if (jr)
	{
		r.x = json_as_number(json_at(jr, 0));
		r.y = json_as_number(json_at(jr, 1));
		r.z = json_as_number(json_at(jr, 2));
		r.w = json_as_number(json_at(jr, 3));
	}
	js = json_get(node, "scale");
	if (js)
	{
		s[0] = json_as_number(json_at(js, 0));
		s[1] = json_as_number(json_at(js, 1));
		s[2] = json_as_number(json_at(js, 2));
	}
	bone->trs.pos = t;
	bone->trs.rot = r;
	bone->trs.scale = vec3(s[0], s[1], s[2]);
	bone->local_transform = make_transform(t, r, s);
	bone->global_transform = bone->local_transform;
	bone->inv_bind_pose = mat4_identity();
	bone->bind_pose = bone->local_transform;
}

void	glb_fill_extra_anim_nodes(t_mesh *mesh, t_json_value *json)
{
	t_json_value	*skins;
	t_json_value	*joints;
	t_json_value	*nodes_arr;
	t_json_value	*node;
	t_json_value	*children;
	t_bone			*bone;
	int				*is_joint;
	int				*parent_map;
	int				node_idx;
	int				par_idx;
	int				skel_idx;
	int				child_idx;
	int				nc;
	int				i;
	int				k;

	if (!mesh->skeleton)
		return ;
	skins = json_get(json, "skins");
	if (!skins)
		return ;
	joints = json_get(json_at(skins, 0), "joints");
	if (!joints)
		return ;
	nodes_arr = json_get(json, "nodes");
	if (!nodes_arr)
		return ;
	nc = (int)nodes_arr->u.array.count;
	is_joint = ft_calloc(65536, sizeof(int));
	parent_map = malloc(sizeof(int) * 65536);
	if (!is_joint || !parent_map)
	{
		free(is_joint);
		free(parent_map);
		return ;
	}
	i = 0;
	while (i < 65536)
		parent_map[i++] = -1;
	i = 0;
	while (i < (int)joints->u.array.count)
	{
		node_idx = (int)json_as_number(json_at(joints, i));
		if (node_idx >= 0 && node_idx < 65536)
			is_joint[node_idx] = 1;
		i++;
	}
	/* Build parent map from each node's children array */
	i = 0;
	while (i < nc && i < 65536)
	{
		node = json_at(nodes_arr, i);
		children = json_get(node, "children");
		if (children)
		{
			k = 0;
			while (k < (int)children->u.array.count)
			{
				child_idx = (int)json_as_number(json_at(children, k));
				if (child_idx >= 0 && child_idx < 65536)
					parent_map[child_idx] = i;
				k++;
			}
		}
		i++;
	}
	/* Add extra bones for non-joint mesh nodes */
	i = 0;
	while (i < nc && i < 65536)
	{
		node = json_at(nodes_arr, i);
		if (!is_joint[i] && (int)json_get_int(node, "mesh") >= 0)
		{
			/* Walk up the hierarchy to find nearest joint ancestor */
			par_idx = parent_map[i];
			skel_idx = -1;
			while (par_idx >= 0 && par_idx < 65536)
			{
				if (is_joint[par_idx])
				{
					k = 0;
					while (k < mesh->bone_count)
					{
						if (mesh->skeleton[k].node_idx == par_idx)
						{
							skel_idx = k;
							break ;
						}
						k++;
					}
					break ;
				}
				par_idx = parent_map[par_idx];
			}
			bone = &mesh->skeleton[mesh->bone_count];
			ft_memset(bone, 0, sizeof(t_bone));
			bone->node_idx = i;
			bone->parent = skel_idx;
			fill_bone_trs(bone, node);
			mesh->bone_matrices[mesh->bone_count] = mat4_identity();
			mesh->bone_count++;
		}
		i++;
	}
	free(is_joint);
	free(parent_map);
	glb_log("GLB: Skeleton extended to %d bones total.\n", mesh->bone_count);
}
