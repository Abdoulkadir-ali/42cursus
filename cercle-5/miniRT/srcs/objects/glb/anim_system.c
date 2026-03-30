/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/17 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"
#include "maths.h"
#include <math.h>
#include <string.h>

/* --- Math Helpers --- */

static t_mat4 quat_to_mat4(double x, double y, double z, double w)
{
	t_mat4 m = mat4_identity();
	double xx = x * x; double yy = y * y; double zz = z * z;
	double xy = x * y; double xz = x * z; double yz = y * z;
	double wx = w * x; double wy = w * y; double wz = w * z;

	// Transposed (v*M)
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

static t_mat4	make_transform_q(t_vec3 t, t_vec3 r_quat, t_vec3 s)
{
	t_mat4 mt = mat4_translation(t);
	t_mat4 mr = quat_to_mat4(r_quat.x, r_quat.y, r_quat.z, r_quat.w);
	t_mat4 ms = mat4_scaling(s);
	
	// S * R * T (Row Major)
	return mat4_mul(ms, mat4_mul(mr, mt));
}

static void quat_slerp(float *out, float *a, float *b, float t)
{
	float dot = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
	float sign = 1.0f;
	if (dot < 0.0f) { dot = -dot; sign = -1.0f; }
	
	if (dot > 0.9995f) {
		// Linear
		for(int i=0; i<4; i++) out[i] = a[i] + t * (sign * b[i] - a[i]);
		// Normalize
		float len = sqrtf(out[0]*out[0] + out[1]*out[1] + out[2]*out[2] + out[3]*out[3]);
		for(int i=0; i<4; i++) out[i] /= len;
		return;
	}
	
	float theta_0 = acosf(dot);
	float theta = theta_0 * t;
	float sin_theta = sinf(theta);
	float sin_theta_0 = sinf(theta_0);
	
	float s0 = cosf(theta) - dot * sin_theta / sin_theta_0;
	float s1 = sin_theta / sin_theta_0;
	
	for(int i=0; i<4; i++) out[i] = s0 * a[i] + s1 * sign * b[i];
}

static void vec3_mix(float *out, float *a, float *b, float t)
{
	out[0] = a[0] + (b[0] - a[0]) * t;
	out[1] = a[1] + (b[1] - a[1]) * t;
	out[2] = a[2] + (b[2] - a[2]) * t;
}

/* --- Sampling --- */

static void sample_channel(t_anim_sampler *sampler, float time, float *result, int stride)
{
	int i = 0;
	/* Clamp time to range */
	if (time <= sampler->inputs[0])
	{
		memcpy(result, &sampler->outputs[0], stride * sizeof(float));
		return;
	}
	if (time >= sampler->inputs[sampler->count - 1])
	{
		memcpy(result, &sampler->outputs[(sampler->count - 1) * stride], stride * sizeof(float));
		return;
	}
	
	/* Linear Scan (optimize later) */
	while (i < sampler->count - 1)
	{
		if (time >= sampler->inputs[i] && time < sampler->inputs[i + 1])
			break;
		i++;
	}
	
	float t0 = sampler->inputs[i];
	float t1 = sampler->inputs[i + 1];
	float factor = (time - t0) / (t1 - t0);
	
	if (sampler->method == INTERP_STEP)
	{
		memcpy(result, &sampler->outputs[i * stride], stride * sizeof(float));
	}
	else if (stride == 4) // Quat
	{
		quat_slerp(result, &sampler->outputs[i * stride], &sampler->outputs[(i + 1) * stride], factor);
	}
	else // Linear Vec3
	{
		vec3_mix(result, &sampler->outputs[i * stride], &sampler->outputs[(i + 1) * stride], factor);
	}
}

/* --- Skeleton Update --- */

static int find_bone(t_mesh *mesh, int node_idx)
{
	for (int i = 0; i < mesh->bone_count; i++)
		if (mesh->skeleton[i].node_idx == node_idx)
			return i;
	return -1;
}

static void update_bone_recursive(t_mesh *mesh, int bone_idx, t_mat4 parent_transform)
{
	t_bone *bone = &mesh->skeleton[bone_idx];
	
	/* Rebuild Local Matrix from TRS */
	bone->local_transform = make_transform_q(bone->trs.pos, bone->trs.rot, bone->trs.scale);
	
	/* Compute Global (Row Major) */
	t_mat4 global = mat4_mul(bone->local_transform, parent_transform);
	bone->global_transform = global;
	
	/* Compute Skin Matrix (Row Major) */
	mesh->bone_matrices[bone_idx] = mat4_mul(bone->inv_bind_pose, global);
	
	/* Recurse children */
	for (int i = 0; i < mesh->bone_count; i++)
	{
		if (mesh->skeleton[i].parent == bone_idx)
			update_bone_recursive(mesh, i, global);
	}
}

/* CPU Skinning */
static void glb_skin_mesh(t_mesh *mesh)
{
	if (!mesh->base_vertices || !mesh->skin_data || !mesh->bone_matrices) return;

	for (int i = 0; i < mesh->vertex_count; i++)
	{
		t_vec3 pos = vec3(0, 0, 0);
		t_vec3 norm = vec3(0, 0, 0);
		t_vec3 base_pos = mesh->base_vertices[i];
		t_vec3 base_norm = mesh->base_normals ? mesh->base_normals[i] : vec3(0, 1, 0);
		double tmp;
		
		t_bone_weight *bw = &mesh->skin_data[i];
		
		for (int k = 0; k < 4; k++)
		{
			int bone_id = bw->bone_ids[k];
			float w = bw->weights[k];
			
			if (bone_id >= 0 && bone_id < mesh->bone_count && w > 0.0f)
			{
				t_mat4 *mat = &mesh->bone_matrices[bone_id];
				
				/* Transform Position (row-vector: v * M) */
				t_vec3 p = mat4_mul_pos(*mat, base_pos);
				pos.x += p.x * w;
				pos.y += p.y * w;
				pos.z += p.z * w;
				
				/* Transform Normal (row-vector: n * M, read columns) */
				t_vec3 n;
				n.x = base_norm.x * mat->m[0][0] + base_norm.y * mat->m[1][0] + base_norm.z * mat->m[2][0];
				n.y = base_norm.x * mat->m[0][1] + base_norm.y * mat->m[1][1] + base_norm.z * mat->m[2][1];
				n.z = base_norm.x * mat->m[0][2] + base_norm.y * mat->m[1][2] + base_norm.z * mat->m[2][2];
				
				norm.x += n.x * w;
				norm.y += n.y * w;
				norm.z += n.z * w;
			}
		}
		
		/* Apply the same Z→Y axis swap as finalize_mesh so output is in renderer space */
		tmp = pos.y;
		pos.y = -pos.z;
		pos.z = tmp;
		mesh->vertices[i] = pos;
		
		if (mesh->normals)
		{
			float len = sqrtf(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z);
			if (len > 0.0001f) { norm.x/=len; norm.y/=len; norm.z/=len; }
			tmp = norm.y;
			norm.y = -norm.z;
			norm.z = tmp;
			mesh->normals[i] = norm;
		}
	}
}

/* Main Animation Update Function. Force-Updated */
void glb_update_mesh_anim(t_mesh *mesh, t_scene *scene, double dt)
{
	if (!mesh->skeleton || scene->clip_count == 0) return;
	/* Non-skinned meshes (cloth, accessories without skin weights) are driven
	** by morph targets which we don't support. Their position is already baked
	** correctly by mesh_apply_transform at load time — leave them static. */
	if (!mesh->skin_data)
		return ;
	
	/* Use mesh->current_anim index */
	if (mesh->anim_clip_count <= 0)
		return ;
	if (mesh->current_anim < 0 || mesh->current_anim >= mesh->anim_clip_count)
		mesh->current_anim = 0; // Default to first
		
	t_animation *anim = &scene->clips[mesh->anim_base + mesh->current_anim];
	
	mesh->anim_time += dt;
	if (mesh->anim_time > anim->max_time)
		mesh->anim_time = fmod(mesh->anim_time, anim->max_time); // Loop
		
	float time = (float)mesh->anim_time;
	
	/* Apply channels to update bone TRS */
	for (int i = 0; i < anim->channel_count; i++)
	{
		t_anim_channel *ch = &anim->channels[i];
		t_anim_sampler *s = &anim->samplers[ch->sampler_idx];
		
		int bone_idx = find_bone(mesh, ch->node_idx);
		if (bone_idx == -1) continue;
		
		t_bone *b = &mesh->skeleton[bone_idx];
		float val[4];
		
		if (ch->path == PATH_TRANSLATION) {
			sample_channel(s, time, val, 3);
			b->trs.pos = vec3(val[0], val[1], val[2]);
		}
		else if (ch->path == PATH_ROTATION) {
			sample_channel(s, time, val, 4);
			b->trs.rot = vec3(val[0], val[1], val[2]);
			b->trs.rot.w = val[3];
		}
		else if (ch->path == PATH_SCALE) {
			sample_channel(s, time, val, 3);
			b->trs.scale = vec3(val[0], val[1], val[2]);
		}
	}
	
	/* Recompute matrices from roots */
	for (int i = 0; i < mesh->bone_count; i++)
	{
		if (mesh->skeleton[i].parent == -1)
			update_bone_recursive(mesh, i, mat4_identity());
	}
	
	/* Perform CPU Skinning, rebuild BVH, and reapply the .rt scene transform. */
	glb_skin_mesh(mesh);
	mesh_build_bvh(mesh);
	/* Reapply the .rt scene transform (rotation/translation/scale) baked at load time.
	** glb_skin_mesh always writes from base_vertices (GLB space), so the scene
	** transform must be reapplied on top every frame. */
	if (mesh->has_scene_transform)
	{
		int		i;
		t_vec3	v;
		t_vec3	n;
		float	len;

		i = 0;
		while (i < mesh->vertex_count)
		{
			mesh->vertices[i] = mat4_mul_pos(mesh->scene_mat, mesh->vertices[i]);
			if (mesh->normals)
			{
				v = mesh->normals[i];
				n.x = v.x * mesh->scene_rot_mat.m[0][0]
					+ v.y * mesh->scene_rot_mat.m[1][0]
					+ v.z * mesh->scene_rot_mat.m[2][0];
				n.y = v.x * mesh->scene_rot_mat.m[0][1]
					+ v.y * mesh->scene_rot_mat.m[1][1]
					+ v.z * mesh->scene_rot_mat.m[2][1];
				n.z = v.x * mesh->scene_rot_mat.m[0][2]
					+ v.y * mesh->scene_rot_mat.m[1][2]
					+ v.z * mesh->scene_rot_mat.m[2][2];
				len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
				if (len > 0.0001f)
				{
					n.x /= len;
					n.y /= len;
					n.z /= len;
				}
				mesh->normals[i] = n;
			}
			i++;
		}
		mesh_build_bvh(mesh);
	}
}
