/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 05:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	solve_quadratic(float a, float b, float c, float *t0, float *t1)
{
	float	disc;
	float	q;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	if (b < 0)
		q = -0.5 * (b - sqrt(disc));
	else
		q = -0.5 * (b + sqrt(disc));
	*t0 = q / a;
	*t1 = c / q;
	if (*t0 > *t1)
	{
		float temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (true);
}

// Intersect strict cone (without base cap yet)
// Equation: (P - C) . A = |P - C| * cos(theta)
// Infinite Cone: (D.A)^2 - cos^2(theta) = 0 logic...
// Let's use standard algebraic cone intersection
// x^2 + z^2 = y^2 * (r/h)^2
bool	intersect_cone(t_ray *ray, t_cone *cone, t_hit *hit)
{
	t_vec3	oc = vec3_sub(ray->origin, cone->pos);
	float	m = (cone->radius * cone->radius) / (cone->height * cone->height);
	
	// A = D.x^2 + D.z^2 - m * D.y^2
	// But arbitrarily oriented... 
	// Let's project ray to local space or use vector math
	
	float	dd = vec3_dot(ray->direction, cone->axis);
	float	od = vec3_dot(oc, cone->axis);
	
	float	a = vec3_dot(ray->direction, ray->direction) - (1 + m) * dd * dd;
	float	b = 2 * (vec3_dot(ray->direction, oc) - (1 + m) * dd * od);
	float	c = vec3_dot(oc, oc) - (1 + m) * od * od;
	
	float t0, t1;
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (false);

	// Check bounds (0 <= y <= height)
	// y = (P - C) . A
	float t = t0;
	float y = od + t * dd;
	bool found = false;

	if (t > 0.001 && y >= 0 && y <= cone->height)
		found = true;
	else
	{
		t = t1;
		y = od + t * dd;
		if (t > 0.001 && y >= 0 && y <= cone->height)
			found = true;
		else
			return (false); // Simplistic, missing cap for now
	}

	if (found && t < hit->t)
	{
		hit->t = t;
		hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		
		float k = cone->radius / cone->height;
		// The generic normal for point P on cone surface:
		// N = P - C - (1 + k^2) * ((P-C).A) * A
		
		t_vec3 temp = vec3_sub(hit->point, cone->pos);
		float scale = (1 + k*k) * vec3_dot(temp, cone->axis);
		hit->normal = vec3_norm(vec3_sub(temp, vec3_scale(cone->axis, scale)));
		
		// Cone UV
		// Use same logic as cylinder for theta, but v uses height
		t_vec3	u_ax, v_ax;
		if (fabs(cone->axis.y) > 0.9) u_ax = vec3(1, 0, 0);
		else u_ax = vec3(0, 1, 0);
		v_ax = vec3_norm(vec3_cross(cone->axis, u_ax));
		u_ax = vec3_norm(vec3_cross(v_ax, cone->axis));
		
		// Project P-C onto cross section
		// h = (P-C).A
		// C_center = C + h*A
		// Radial = P - C_center
		// u is angle of Radial
		
		float h = vec3_dot(temp, cone->axis);
		t_vec3 center_h = vec3_add(cone->pos, vec3_scale(cone->axis, h));
		t_vec3 radial = vec3_sub(hit->point, center_h);
		
		double u_val = vec3_dot(radial, u_ax);
		double v_val = vec3_dot(radial, v_ax);
		hit->u = (atan2(v_val, u_val) + M_PI) / (2 * M_PI);
		hit->v = h / cone->height;

		// Tangents
		// Similar to cylinder, tangent is across flow
		hit->tangent = vec3_norm(vec3_cross(hit->normal, cone->axis));
		hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
		
		// Base cap intersection check would go here later
		
		if (vec3_dot(hit->normal, ray->direction) > 0)
			hit->normal = vec3_scale(hit->normal, -1);
		return (true);
	}
	return (false);
}

