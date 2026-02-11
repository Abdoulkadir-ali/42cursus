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
#include "debug.h"

static inline bool	intersect_triangle_fast(const t_ray *ray, t_vec3 v[3],
		double *t, t_vec2 *uv)
{
	t_vec3	e1 = vec3_sub(v[1], v[0]);
	t_vec3	e2 = vec3_sub(v[2], v[0]);
	t_vec3	pvec = vec3_cross(ray->direction, e2);
	double	det = vec3_dot(e1, pvec);
	
	/* Double-sided: check if det is close to 0 */
	if (fabs(det) < 1e-8) { if (0) ft_print_debug("DEBUG: Tri Fail (Det ~0)\n"); return (false); }
	double	inv_det = 1.0 / det;
	t_vec3	tvec = vec3_sub(ray->origin, v[0]);
	double	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0) return (false);
	t_vec3	qvec = vec3_cross(tvec, e1);
	double	v_val = vec3_dot(ray->direction, qvec) * inv_det;
	if (v_val < 0.0 || u + v_val > 1.0) return (false);
	*t = vec3_dot(e2, qvec) * inv_det;
	if (uv) { uv->x = u; uv->y = v_val; }
	if (*t <= EPSILON) return (false);
	return (true);
	return (true);
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
		t_vec3 sh_n;

		sh_n = vec3_add(vec3_scale(n0, 1.0 - bary.x - bary.y),
					vec3_add(vec3_scale(n1, bary.x), vec3_scale(n2, bary.y)));
		hit->normal = vec3_norm(sh_n);
		
		if (0) /* DEBUG NORMALS DETAIL */
			printf("DEBUG: Tri %d Interp Normal: (%.2f, %.2f, %.2f) from N0(%.2f) N1(%.2f) N2(%.2f) uv(%.2f, %.2f)\n",
				tri_idx, hit->normal.x, hit->normal.y, hit->normal.z,
				n0.x, n1.x, n2.x, bary.x, bary.y);
	}
	else
	{
		hit->normal = vec3_norm(vec3_cross(vec3_sub(v1, v0), vec3_sub(v2, v0)));
		if (0) printf("DEBUG: Tri %d FLAT Normal (No Vertex Normals)\n", tri_idx);
	}
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
	int		stack[64];
	int		top;
	int		node_idx;
	int		best_tri;
	double	best_t;
	double	t_min, t_max;
	double	tl_min, tl_max, tr_min, tr_max;
	t_vec2	best_uv;
	t_mbvh_node	*node;
	int		left_idx, right_idx;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	top = 0;
	node_idx = 0;
	best_tri = -1;
	hit->t = MAX_VALUE;
	best_t = hit->t;
	stack[top++] = 0; /* Push root */

	while (top > 0)
	{
		node_idx = stack[--top];
		node = &mesh->bvh_nodes[node_idx];

		if (!aabb_intersect_fast(&node->bbox, ray, &t_min, &t_max) || t_min >= best_t)
		{
			continue ;
		}

		if (node->count > 0) /* Leaf */
		{
			for (int i = 0; i < node->count; i++)
			{
				int tri = node->left_or_first + i;
				int *idx = &mesh->bvh_indices[tri * 3];
				t_vec3 v[3] = {mesh->vertices[idx[0]], mesh->vertices[idx[1]], mesh->vertices[idx[2]]};
				double t; 
				t_vec2 uv;
				if (intersect_triangle_fast(ray, v, &t, &uv) && t < best_t)
				{
					best_t = t; 
					best_tri = tri; 
					best_uv = uv;
				}
				else if (0) /* Very verbose */
					debug_print_triangle_test(tri, v);
			}
		}
		else /* Interior */
		{
			/* Front-to-back traversal: check children distances */
			left_idx = node_idx + 1;
			right_idx = node->left_or_first;
			
			bool hit_l = aabb_intersect_fast(&mesh->bvh_nodes[left_idx].bbox, ray, &tl_min, &tl_max);
			bool hit_r = aabb_intersect_fast(&mesh->bvh_nodes[right_idx].bbox, ray, &tr_min, &tr_max);

			if (hit_l && hit_r)
			{
				if (tl_min > tr_min) /* Left is further, push first (process last) */
				{
					stack[top++] = left_idx;
					stack[top++] = right_idx;
				}
				else
				{
					stack[top++] = right_idx;
					stack[top++] = left_idx;
				}
			}
			else if (hit_l) stack[top++] = left_idx;
			else if (hit_r) stack[top++] = right_idx;
		}
	}
	if (best_tri != -1) 
	{ 
		update_mesh_hit(hit, best_t, mesh, best_tri, ray, best_uv); 
		return (true); 
	}
	return (false);
}

bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist)
{
	int		stack[64];
	int		top;
	int		node_idx;
	double	t_min, t_max;
	double	tl_min, tl_max, tr_min, tr_max;
	t_mbvh_node	*node;
	int		left_idx, right_idx;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	top = 0;
	node_idx = 0;
	stack[top++] = 0;

	while (top > 0)
	{
		node_idx = stack[--top];
		node = &mesh->bvh_nodes[node_idx];

		if (!aabb_intersect_fast(&node->bbox, ray, &t_min, &t_max) || t_min >= dist)
			continue ;

		if (node->count > 0) /* Leaf */
		{
			for (int i = 0; i < node->count; i++)
			{
				int tri = node->left_or_first + i;
				int *idx = &mesh->bvh_indices[tri * 3];
				t_vec3 v[3] = {mesh->vertices[idx[0]], mesh->vertices[idx[1]], mesh->vertices[idx[2]]};
				double t;
				if (intersect_triangle_fast(ray, v, &t, NULL) && t < dist)
					return (true);
			}
		}
		else
		{
			/* Front-to-back traversal: check children distances */
			left_idx = node_idx + 1;
			right_idx = node->left_or_first;
			
			bool hit_l = aabb_intersect_fast(&mesh->bvh_nodes[left_idx].bbox, ray, &tl_min, &tl_max);
			bool hit_r = aabb_intersect_fast(&mesh->bvh_nodes[right_idx].bbox, ray, &tr_min, &tr_max);

			if (hit_l && hit_r)
			{
				if (tl_min > tr_min) /* Left is further, push first (process last) */
				{
					stack[top++] = left_idx;
					stack[top++] = right_idx;
				}
				else
				{
					stack[top++] = right_idx;
					stack[top++] = left_idx;
				}
			}
			else if (hit_l) stack[top++] = left_idx;
			else if (hit_r) stack[top++] = right_idx;
		}
	}
	return (false);
}
