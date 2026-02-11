/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static inline bool	intersect_triangle_fast(const t_ray *ray, t_vec3 v[3],
		double *t, t_vec2 *uv)
{
	t_vec3	e1 = vec3_sub(v[1], v[0]);
	t_vec3	e2 = vec3_sub(v[2], v[0]);
	t_vec3	pvec = vec3_cross(ray->direction, e2);
	double	det = vec3_dot(e1, pvec);
	if (det > -1e-8 && det < 1e-8) return (false);
	double	inv_det = 1.0 / det;
	t_vec3	tvec = vec3_sub(ray->origin, v[0]);
	double	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0) return (false);
	t_vec3	qvec = vec3_cross(tvec, e1);
	double	v_val = vec3_dot(ray->direction, qvec) * inv_det;
	if (v_val < 0.0 || u + v_val > 1.0) return (false);
	*t = vec3_dot(e2, qvec) * inv_det;
	if (uv) { uv->x = u; uv->y = v_val; }
	return (*t > EPSILON);
}

static void	update_mesh_hit(t_hit *hit, double t, t_mesh *mesh, int tri_idx,
		const t_ray *ray, t_vec2 bary)
{
	int		*idx = &mesh->bvh_indices[tri_idx * 3];
	t_vec3	v0 = mesh->vertices[idx[0]];
	t_vec3	v1 = mesh->vertices[idx[1]];
	t_vec3	v2 = mesh->vertices[idx[2]];

	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	if (mesh->normals)
	{
		t_vec3 n0 = mesh->normals[idx[0]];
		t_vec3 n1 = mesh->normals[idx[1]];
		t_vec3 n2 = mesh->normals[idx[2]];
		hit->normal = vec3_norm(vec3_add(vec3_scale(n0, 1.0 - bary.x - bary.y),
					vec3_add(vec3_scale(n1, bary.x), vec3_scale(n2, bary.y))));
	}
	else
		hit->normal = vec3_norm(vec3_cross(vec3_sub(v1, v0), vec3_sub(v2, v0)));
	if (mesh->uvs)
	{
		t_vec2 t0 = mesh->uvs[idx[0]];
		t_vec2 t1 = mesh->uvs[idx[1]];
		t_vec2 t2 = mesh->uvs[idx[2]];
		hit->u = t0.x * (1.0 - bary.x - bary.y) + t1.x * bary.x + t2.x * bary.y;
		hit->v = t0.y * (1.0 - bary.x - bary.y) + t1.y * bary.x + t2.y * bary.y;
	}
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
}

bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit)
{
	int		stack[64], top = 0, node_idx = 0;
	int		best_tri = -1;
	double	best_t = hit->t, t_ear, t_far;
	t_vec2	best_uv;

	if (!mesh || !mesh->bvh_nodes) return (false);
	while (1)
	{
		t_mbvh_node *node = &mesh->bvh_nodes[node_idx];
		if (!aabb_intersect_fast(&node->bbox, ray, &t_ear, &t_far) || t_ear > best_t)
		{
			if (top == 0) break;
			node_idx = stack[--top];
			continue ;
		}
		if (node->count > 0) /* Leaf */
		{
			for (int i = 0; i < node->count; i++)
			{
				int tri = node->left_or_first + i;
				int *idx = &mesh->bvh_indices[tri * 3];
				t_vec3 v[3] = {mesh->vertices[idx[0]], mesh->vertices[idx[1]], mesh->vertices[idx[2]]};
				double t; t_vec2 uv;
				if (intersect_triangle_fast(ray, v, &t, &uv) && t < best_t)
				{
					best_t = t; best_tri = tri; best_uv = uv;
				}
			}
			if (top == 0) break;
			node_idx = stack[--top];
		}
		else /* Interior */
		{
			/* Front-to-back: Visit node closer to ray origin first */
			int near = node_idx + 1;
			int far = node->left_or_first;
			if (ray->sign[node->axis]) { near = node->left_or_first; far = node_idx + 1; }
			
			node_idx = near;
			stack[top++] = far;
		}
	}
	if (best_tri != -1) { update_mesh_hit(hit, best_t, mesh, best_tri, ray, best_uv); return (true); }
	return (false);
}

bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist)
{
	int		stack[64], top = 0, node_idx = 0;
	double	t_ear, t_far;

	if (!mesh || !mesh->bvh_nodes) return (false);
	while (1)
	{
		t_mbvh_node *node = &mesh->bvh_nodes[node_idx];
		if (!aabb_intersect_fast(&node->bbox, ray, &t_ear, &t_far) || t_ear > dist)
		{
			if (top == 0) break;
			node_idx = stack[--top];
			continue ;
		}
		if (node->count > 0)
		{
			for (int i = 0; i < node->count; i++)
			{
				int tri = node->left_or_first + i;
				int *idx = &mesh->bvh_indices[tri * 3];
				t_vec3 v[3] = {mesh->vertices[idx[0]], mesh->vertices[idx[1]], mesh->vertices[idx[2]]};
				double t;
				if (intersect_triangle_fast(ray, v, &t, NULL) && t < dist) return (true);
			}
			if (top == 0) break;
			node_idx = stack[--top];
		}
		else
		{
			int near = node_idx + 1;
			int far = node->left_or_first;
			if (ray->sign[node->axis]) { near = node->left_or_first; far = node_idx + 1; }
			
			node_idx = near;
			stack[top++] = far;
		}
	}
	return (false);
}
