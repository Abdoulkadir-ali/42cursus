/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 19:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
}

void	ray_normalize_direction(t_ray *ray)
{
	ray->direction = vec3_norm(ray->direction);
}

static bool	solve_quadratic(double a, double b, double c, double *t1,
		double *t2)
{
	double	discriminant;
	double	sqrt_d;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_d = sqrt(discriminant);
	*t1 = (-b - sqrt_d) / (2 * a);
	*t2 = (-b + sqrt_d) / (2 * a);
	return (true);
}

bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vec3	center;
	double	a, b, c, t, t1, t2;

	center = sp->pos;
	t_vec3 oc = vec3_sub(ray->origin, center);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - sp->radius_sq;
	if (!solve_quadratic(a, b, c, &t1, &t2))
		return (false);
	t = (t1 > 0) ? t1 : t2;
	if (t < 0)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = vec3_scale(vec3_sub(hit->point, center), 1.0 / sqrt(sp->radius_sq));
	
	// Sphere UV & Tangents
	double theta = acos(-hit->normal.y);
	double phi = atan2(-hit->normal.z, hit->normal.x) + M_PI;
	hit->u = phi / (2 * M_PI);
	hit->v = theta / M_PI;

	// Tangents
	t_vec3 up = vec3(0, 1, 0);
	if (fabs(vec3_dot(hit->normal, up)) > 0.99)
		up = vec3(0, 0, 1);
	hit->tangent = vec3_norm(vec3_cross(up, hit->normal));
	hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
	
	return (true);
}

// Helper for Plane UV
static void	get_plane_uv(t_vec3 p, t_vec3 n, double *u, double *v, t_vec3 *tangent, t_vec3 *bitangent)
{
	t_vec3	u_axis, v_axis;
	
	// Pick an arbitrary axis to cross with normal
	if (fabs(n.y) > 0.9)
		u_axis = vec3(1, 0, 0); // If normal is Y, use X
	else
		u_axis = vec3(0, 1, 0); // Else use Y
	
	v_axis = vec3_norm(vec3_cross(n, u_axis));
	u_axis = vec3_norm(vec3_cross(v_axis, n));
	
	*u = vec3_dot(p, u_axis);
	*v = vec3_dot(p, v_axis);
	
	// Scale slightly to make texture repeat visible
	*u *= 0.1;
	*v *= 0.1;

	*tangent = u_axis;
	*bitangent = v_axis;
}

bool	intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit)
{
	t_vec3	point, normal;
	double	denom, t;

	normal = pl->normal;
	point = pl->pos;
	denom = vec3_dot(normal, ray->direction);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(point, ray->origin), normal) / denom;
	if (t < 0)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = normal;
	if (vec3_dot(ray->direction, normal) > 0)
		hit->normal = vec3_scale(normal, -1.0);
	
	// Plane UV
	get_plane_uv(hit->point, pl->normal, &hit->u, &hit->v, &hit->tangent, &hit->bitangent);

	return (true);
}

bool	intersect_cone(const t_ray *ray, t_cone *co, t_hit *hit);

bool	intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	// Keep cylinder logic for now, but ensure it's consistent
	t_vec3	center = cy->pos;
	t_vec3	axis = cy->axis;
	double	radius = cy->radius;
	double	height = cy->height;
	t_vec3	oc = vec3_sub(ray->origin, center);
	
	double	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, axis), 2);
	double	b = 2.0 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction, axis) * vec3_dot(oc, axis));
	double	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, axis), 2) - radius * radius;
	
	double	t_min = DBL_MAX;
	t_vec3	n = vec3(0,0,0);
	bool	hit_found = false;
	
	// Store tangent basis for later
	t_vec3	final_u_ax, final_v_ax;

	// Body intersection
	double	t1, t2;
	if (solve_quadratic(a, b, c, &t1, &t2))
	{
		if (t1 > 0)
		{
			t_vec3 pt = vec3_add(ray->origin, vec3_scale(ray->direction, t1));
			double h = vec3_dot(vec3_sub(pt, center), axis);
			if (h >= 0 && h <= height)
			{
				t_min = t1;
				n = vec3_norm(vec3_sub(vec3_sub(pt, center), vec3_scale(axis, h)));
				hit_found = true;
				
				// Cylindrical UV
				t_vec3	u_ax, v_ax;
				if (fabs(axis.y) > 0.9) u_ax = vec3(1, 0, 0);
				else u_ax = vec3(0, 1, 0);
				v_ax = vec3_norm(vec3_cross(axis, u_ax));
				u_ax = vec3_norm(vec3_cross(v_ax, axis));
				
				double u_val = vec3_dot(vec3_sub(pt, center), u_ax);
				double v_val = vec3_dot(vec3_sub(pt, center), v_ax);
				hit->u = (atan2(v_val, u_val) + M_PI) / (2 * M_PI);
				hit->v = h / height;
				
				// Tangents
				// V is along axis (ish)
				// U is around axis
				// U direction is tangent to circle -> Cross(N, Axis)
				final_u_ax = vec3_norm(vec3_cross(n, axis)); 
				final_v_ax = vec3_norm(vec3_cross(n, final_u_ax)); // Vertical-ish
			}
		}
		if (!hit_found && t2 > 0 && t2 < t_min)
		{
			t_vec3 pt = vec3_add(ray->origin, vec3_scale(ray->direction, t2));
			double h = vec3_dot(vec3_sub(pt, center), axis);
			if (h >= 0 && h <= height)
			{
				t_min = t2;
				n = vec3_norm(vec3_sub(vec3_sub(pt, center), vec3_scale(axis, h)));
				hit_found = true;
				
				// Cylindrical UV (Repeat)
				t_vec3	u_ax, v_ax;
				if (fabs(axis.y) > 0.9) u_ax = vec3(1, 0, 0);
				else u_ax = vec3(0, 1, 0);
				v_ax = vec3_norm(vec3_cross(axis, u_ax));
				u_ax = vec3_norm(vec3_cross(v_ax, axis));
				
				double u_val = vec3_dot(vec3_sub(pt, center), u_ax);
				double v_val = vec3_dot(vec3_sub(pt, center), v_ax);
				hit->u = (atan2(v_val, u_val) + M_PI) / (2 * M_PI);
				hit->v = h / height;
				
				final_u_ax = vec3_norm(vec3_cross(n, axis));
				final_v_ax = vec3_norm(vec3_cross(n, final_u_ax));
			}
		}
	}

	// Cap Intersection Helper
	// Plane 1: (p - center) . axis = 0 (Bottom)
	// Plane 2: (p - (center + axis*height)) . axis = 0 (Top)
	
	// Bottom Cap
	double denom = vec3_dot(ray->direction, axis);
	if (fabs(denom) > 1e-6)
	{
		double t_cap = vec3_dot(vec3_sub(center, ray->origin), axis) / denom;
		if (t_cap > 0 && t_cap < t_min)
		{
			t_vec3 p = vec3_add(ray->origin, vec3_scale(ray->direction, t_cap));
			t_vec3 v = vec3_sub(p, center);
			if (vec3_dot(v, v) <= radius * radius)
			{
				t_min = t_cap;
				n = vec3_scale(axis, -1.0); // Pointing down/out from bottom
				hit_found = true;
				
				// Cap UV (Planar mapping on cap)
				t_vec3	u_ax, v_ax;
				if (fabs(axis.y) > 0.9) u_ax = vec3(1, 0, 0);
				else u_ax = vec3(0, 1, 0);
				v_ax = vec3_norm(vec3_cross(axis, u_ax));
				u_ax = vec3_norm(vec3_cross(v_ax, axis));
				hit->u = (vec3_dot(v, u_ax) / radius + 1) * 0.5;
				hit->v = (vec3_dot(v, v_ax) / radius + 1) * 0.5;
				
				final_u_ax = u_ax;
				final_v_ax = v_ax;
			}
		}
		
		// Top Cap
		t_vec3 top_center = vec3_add(center, vec3_scale(axis, height));
		t_cap = vec3_dot(vec3_sub(top_center, ray->origin), axis) / denom;
		if (t_cap > 0 && t_cap < t_min)
		{
			t_vec3 p = vec3_add(ray->origin, vec3_scale(ray->direction, t_cap));
			t_vec3 v = vec3_sub(p, top_center);
			if (vec3_dot(v, v) <= radius * radius)
			{
				t_min = t_cap;
				n = axis; // Pointing up/out from top
				hit_found = true;

				// Cap UV
				t_vec3	u_ax, v_ax;
				if (fabs(axis.y) > 0.9) u_ax = vec3(1, 0, 0);
				else u_ax = vec3(0, 1, 0);
				v_ax = vec3_norm(vec3_cross(axis, u_ax));
				u_ax = vec3_norm(vec3_cross(v_ax, axis));
				hit->u = (vec3_dot(v, u_ax) / radius + 1) * 0.5;
				hit->v = (vec3_dot(v, v_ax) / radius + 1) * 0.5;
				
				final_u_ax = u_ax;
				final_v_ax = v_ax;
			}
		}
	}

	if (!hit_found)
		return (false);

	hit->t = t_min;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t_min));
	hit->normal = n;
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	
	hit->tangent = final_u_ax;
	hit->bitangent = final_v_ax;

	return (true);

}

bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref, t_hit *hit)
{
	bool res = false;

	if (ref.type == TYPE_SPHERE)
		res = intersect_sphere(ray, &scene->spheres[ref.index], hit);
	else if (ref.type == TYPE_PLANE)
		res = intersect_plane(ray, &scene->planes[ref.index], hit);
	else if (ref.type == TYPE_MESH)
		res = intersect_mesh(ray, &scene->meshes[ref.index], hit);
	else if (ref.type == TYPE_ANIM)
		res = intersect_mesh(ray, &scene->animated[ref.index].base, hit);
	else if (ref.type == TYPE_CYLINDER)
		res = intersect_cylinder(ray, &scene->cylinders[ref.index], hit);
	else if (ref.type == TYPE_CONE)
		res = intersect_cone(ray, &scene->cones[ref.index], hit);
	
	if (res)
		hit->ref = ref;
	return (res);
}

static bool	aabb_ray_intersect(const t_aabb *aabb, const t_ray *ray,
		double *tmin, double *tmax)
{
	double	t1, t2;
	double	tmin_val = -DBL_MAX;
	double	tmax_val = DBL_MAX;

	// X
	t1 = (aabb->min.x - ray->origin.x) / ray->direction.x;
	t2 = (aabb->max.x - ray->origin.x) / ray->direction.x;
	tmin_val = fmax(tmin_val, fmin(t1, t2));
	tmax_val = fmin(tmax_val, fmax(t1, t2));
	// Y
	t1 = (aabb->min.y - ray->origin.y) / ray->direction.y;
	t2 = (aabb->max.y - ray->origin.y) / ray->direction.y;
	tmin_val = fmax(tmin_val, fmin(t1, t2));
	tmax_val = fmin(tmax_val, fmax(t1, t2));
	// Z
	t1 = (aabb->min.z - ray->origin.z) / ray->direction.z;
	t2 = (aabb->max.z - ray->origin.z) / ray->direction.z;
	tmin_val = fmax(tmin_val, fmin(t1, t2));
	tmax_val = fmin(tmax_val, fmax(t1, t2));

	*tmin = tmin_val;
	*tmax = tmax_val;
	return (tmax_val >= tmin_val && tmax_val > 0);
}

static void	bvh_traverse(const t_bvh *bvh, const t_bvh_node *node, const t_ray *ray, t_hit *hit)
{
	t_hit	temp_hit = {0};
	temp_hit.t = DBL_MAX;
	double	tmin, tmax;

	if (!node)
		return ;
	if (!aabb_ray_intersect(&node->bbox, ray, &tmin, &tmax) || tmax < 0
		|| tmin > hit->t)
		return ;
	if (node->left || node->right)
	{
		bvh_traverse(bvh, node->left, ray, hit);
		bvh_traverse(bvh, node->right, ray, hit);
	}
	else
	{
		for (size_t i = 0; i < node->num_refs; ++i)
		{
			if (intersect_object(ray, bvh->scene, node->refs[i], &temp_hit)
				&& temp_hit.t < hit->t)
			{
				*hit = temp_hit;
			}
		}
	}
}

bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || !bvh->root)
		return (false);
	hit->t = DBL_MAX;
	hit->ref.type = TYPE_NONE;
	bvh_traverse(bvh, bvh->root, ray, hit);
	return (hit->ref.type != TYPE_NONE);
}

t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene)
{
	t_hit	hit;

	bool hit_any = bvh_intersect(bvh, ray, &hit);
	
	// Check infinite planes separately
	for (int i = 0; i < scene->plane_count; i++)
	{
		t_hit plane_hit;
		if (intersect_plane(ray, &scene->planes[i], &plane_hit))
		{
			if (!hit_any || plane_hit.t < hit.t)
			{
				hit = plane_hit;
				hit.ref.type = TYPE_PLANE;
				hit.ref.index = i;
				hit_any = true;
			}
		}
	}

	if (hit_any)
		return (compute_color(&hit, scene, bvh, ray, 0));

	return (vec3(0, 0, 0)); // Background color (maybe from scene->ambient?)
}
