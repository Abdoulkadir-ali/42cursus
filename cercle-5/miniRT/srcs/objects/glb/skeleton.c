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

void	glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin)
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
	
	glb_log("GLB: Building skeleton with %d bones (IBM acc: %d)...\n", 
		count, (int)json_get_int(skin, "inverseBindMatrices"));

	mesh->skeleton = malloc(sizeof(t_bone) * count);
	mesh->bone_matrices = malloc(sizeof(t_mat4) * count);
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
}
