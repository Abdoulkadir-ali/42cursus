/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:22:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/20 18:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Helper to convert degrees to radians
*/
static float	to_radians(float deg)
{
	return (deg * (M_PI / 180.0f));
}

/*
** Unified Projection Matrix Generator
** Handles both Parallel (Shear) and Conic (FOV) modes via 'alpha'.
*/
t_matrix4	get_projection_matrix(t_camera *cam, float aspect)
{
	t_matrix4	mat;
	float		size;
	float		cotan;
	float		fov;
	float		tan_half_fov;

	ft_memset(&mat, 0, sizeof(t_matrix4));
	if (cam->projection == PROJ_PARALLEL)
	{
		// === MODE PARALLÈLE ===
		// alpha controls Angle of Incidence (Shear)
		
		size = 10.0f; // Base view size
		mat.m[0][0] = 1.0f / (size * aspect);
		mat.m[1][1] = 1.0f / size;
		mat.m[2][2] = -2.0f / (10000.0f - 0.1f); // Z-Normalization
		
		// Apply Shear if alpha != 90
		if (fabs(cam->alpha - 90.0f) > 0.001f)
		{
			cotan = 1.0f / tanf(to_radians(cam->alpha));
			mat.m[0][2] = cotan; // Shear X by Z
			mat.m[1][2] = cotan; // Shear Y by Z
			
			// Matrix Compensation:
			// The object is shifted by Z = -500.0 before projection.
			// Shear = Z * cotan.
			// This causes a massive drift: -500 * cotan.
			// We effectively "pull back" the camera by adding the inverse translation.
			mat.m[0][3] = -(-500.0f * cotan); 
			mat.m[1][3] = -(-500.0f * cotan);
		}
		mat.m[3][3] = 1.0f;
	}
	else
	{
		// === MODE CONIQUE ===
		// alpha controls FOV (Aperture)
		
		fov = cam->alpha;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 179.0f)
			fov = 179.0f;
			
		tan_half_fov = tanf(to_radians(fov) / 2.0f);
		
		mat.m[0][0] = 1.0f / (aspect * tan_half_fov);
		mat.m[1][1] = 1.0f / tan_half_fov;
		mat.m[2][2] = -1.0f;
		mat.m[2][3] = -2.0f * 0.1f; // Near plane offset
		mat.m[3][2] = -1.0f; // Perspective divide enabler
		mat.m[3][3] = 0.0f;
	}
	return (mat);
}

void	calculate_transform_matrix(t_camera *cam)
{
	t_matrix4	view;
	t_matrix4	proj;
	t_matrix4	mvp;
	float		cam_dist;
	float		scale_factor;

	/* 1. Model Matrix: Center and Scale Z */
	/* We handle centering manually in apply_transform due to effective_center.z dependency */
	/* So here model is Identity effectively for position, but rotation is separate. */
	
	/* 2. View Matrix: Rotation & Translation (Dolly) */
	/* Rotation is currently 3x3 in cam struct. We'll apply it manually or convert. */
	/* For now, to keep it compatible with existing rotation struct, we will mix techniques. */
	/* Ideally we convert 3x3 rotation to 4x4. */
	
	/* Actually, let's build the full 4x4. */
	/* Rotation */
	t_matrix4 rot = matrix_identity();
	rot.m[0][0] = (float)cam->rotation_matrix[0].x;
	rot.m[0][1] = (float)cam->rotation_matrix[0].y;
	rot.m[0][2] = (float)cam->rotation_matrix[0].z;
	rot.m[1][0] = (float)cam->rotation_matrix[1].x;
	rot.m[1][1] = (float)cam->rotation_matrix[1].y;
	rot.m[1][2] = (float)cam->rotation_matrix[1].z;
	rot.m[2][0] = (float)cam->rotation_matrix[2].x;
	rot.m[2][1] = (float)cam->rotation_matrix[2].y;
	rot.m[2][2] = (float)cam->rotation_matrix[2].z;

	/* Dolly Translate */
	cam_dist = 500.0f;
	if (cam->projection == PROJ_CONIC)
	{
		float tan_half = tanf(to_radians(cam->alpha) / 2.0f);
		if (tan_half < 0.001f) tan_half = 0.001f;
		cam_dist = 500.0f / tan_half; 
	}
	t_matrix4 translate = matrix_translation(0, 0, -cam_dist);
	
	/* View = Translate * Rotate */
	view = matrix_multiply(translate, rot);

	/* 3. Projection Matrix */
	proj = get_projection_matrix(cam, 1.0f);

	/* 4. Screen Scale (Viewport) */
	scale_factor = 50.0f; 
	if (cam->projection == PROJ_CONIC)
		scale_factor *= 30.0f;
	scale_factor *= cam->scale;
	
	t_matrix4 screen_scale = matrix_scale(scale_factor, scale_factor, 1.0f);
	
	/* MVP = Screen * Proj * View */
	/* Order: Proj * View works for column vector v: P * V * v */
	mvp = matrix_multiply(proj, view);
	
	/* We fold the 'screen scale' into the matrix to save muls later */
	cam->transform_matrix = matrix_multiply(screen_scale, mvp);
}

t_point	apply_transform(t_point p, t_camera *cam)
{
	t_vec3d		v;
	t_point		res;
	t_matrix4	*m;
	float		x, y, z, w;

	/* 1. Pre-Matrix Adjustments (Model Space) */
	t_vec3d effective_center = cam->grid_center;
	effective_center.z *= cam->z_scale;
	
	v.x = p.pos.x - effective_center.x;
	v.y = p.pos.y - effective_center.y;
	v.z = p.pos.z - effective_center.z;
	
	/* 2. Matrix Application (MVP + ScreenScale) */
	m = &cam->transform_matrix;
	x = (float)v.x * m->m[0][0] + (float)v.y * m->m[0][1] + (float)v.z * m->m[0][2] + m->m[0][3];
	y = (float)v.x * m->m[1][0] + (float)v.y * m->m[1][1] + (float)v.z * m->m[1][2] + m->m[1][3];
	z = (float)v.x * m->m[2][0] + (float)v.y * m->m[2][1] + (float)v.z * m->m[2][2] + m->m[2][3];
	w = (float)v.x * m->m[3][0] + (float)v.y * m->m[3][1] + (float)v.z * m->m[3][2] + m->m[3][3];

	/* 3. Perspective Divide */
	if (w != 0.0f)
	{
		float inv_w = 1.0f / w;
		x *= inv_w;
		y *= inv_w;
	}

	/* 4. Post-Matrix Offset (Screen Center) */
	res.pos.x = x + cam->offset.x;
	res.pos.y = y + cam->offset.y;
	res.pos.z = z; /* View Space Z from Matrix usually, or just Z? */
	/* Correction: Our matrix Z row (2) outputs -1 etc. */
	/* We need the Z before projection for depth sorting usually. */
	/* But with existing logic, let's trust the Z output from matrix if P is correct. */
	/* The 'z' computed above is affected by Z-normalization in P matrix. */
	/* Should be fine for z-buffer. */
	
	res.color = p.color;
	return (res);
}

/*
** Unified Projection Function
** Legacy Wrapper or Single Point Usage
*/
t_point	project_unified(t_point p3d, t_camera *cam)
{
	/* Ensure matrix is up to date? Caller responsibility for bulk. */
	/* For single point, we just calc it. */
	calculate_transform_matrix(cam);
	return (apply_transform(p3d, cam));
}
