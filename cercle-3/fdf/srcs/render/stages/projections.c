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
#include "graphics.h"

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
	cam->view_dist = cam_dist;
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
	mvp = matrix_multiply(proj, view);
	cam->transform_matrix = matrix_multiply(screen_scale, mvp);
}

t_point	apply_transform(t_point p, t_camera *cam)
{
	t_vec3d		v;
	t_point		res;
	t_matrix4	*m;
	float		x, y, w;

	/* 1. Pre-Matrix Adjustments (Model Space) */
	/* 1. Pre-Matrix Adjustments (Model Space) */
	t_vec3d effective_center_scaled;
	t_vec3d scaled_pos;

	effective_center_scaled = cam->grid_center;
	effective_center_scaled.z *= cam->z_scale;

	scaled_pos = p.pos;
	scaled_pos.z *= cam->z_scale;

	v.x = p.pos.x - effective_center_scaled.x;
	v.y = p.pos.y - effective_center_scaled.y;
	v.z = scaled_pos.z - effective_center_scaled.z;
	
	/* 2. Matrix Application (MVP + ScreenScale) */
	m = &cam->transform_matrix;
	x = (float)v.x * m->m[0][0] + (float)v.y * m->m[0][1] + (float)v.z * m->m[0][2] + m->m[0][3];
	y = (float)v.x * m->m[1][0] + (float)v.y * m->m[1][1] + (float)v.z * m->m[1][2] + m->m[1][3];
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
	
	/* 5. Calculate View-Space Z for Z-Buffer (Legacy Behavior) */
	/* view_z = (Rot * v).z - cam_dist */
	/* Uses 3x3 rotation matrix directly since it's available and correct */
	res.pos.z = v.x * cam->rotation_matrix[2].x + 
				v.y * cam->rotation_matrix[2].y + 
				v.z * cam->rotation_matrix[2].z - cam->view_dist;
	
	res.color = p.color;
	return (res);
}

/*
** Unified Projection Function
** Legacy Wrapper or Single Point Usage
*/
t_point	project_unified(t_point p3d, t_camera *cam)
{
	calculate_transform_matrix(cam);
	return (apply_transform(p3d, cam));
}

/*
** SIMD Optimized Scanline Transformer (AVX2 / Double Precision)
** Processes 4 points (t_vec3d) at a time.
*/
void	transform_scanline(t_graphics *g, t_point *out, size_t row_idx, size_t width)
{
	size_t		i;
	t_vec3d		*in_pos;
	unsigned int *in_col;
	t_camera	*cam;
	t_matrix4	*m;
	
	in_pos = g->map->points.pos;
	in_col = g->map->points.color;
	cam = g->camera;
	m = &cam->transform_matrix;
	
	/* Constants for vectorization */
	/* 1. Rot Matrix Columns for Z-calc */
	__m256d rot0 = _mm256_set1_pd(cam->rotation_matrix[2].x);
	__m256d rot1 = _mm256_set1_pd(cam->rotation_matrix[2].y);
	__m256d rot2 = _mm256_set1_pd(cam->rotation_matrix[2].z);
	__m256d vdist = _mm256_set1_pd(cam->view_dist);
	
	/* 2. Transform Matrix Columns */
	__m256d m00 = _mm256_set1_pd(m->m[0][0]);
	__m256d m01 = _mm256_set1_pd(m->m[0][1]);
	__m256d m02 = _mm256_set1_pd(m->m[0][2]);
	__m256d m03 = _mm256_set1_pd(m->m[0][3]);

	__m256d m10 = _mm256_set1_pd(m->m[1][0]);
	__m256d m11 = _mm256_set1_pd(m->m[1][1]);
	__m256d m12 = _mm256_set1_pd(m->m[1][2]);
	__m256d m13 = _mm256_set1_pd(m->m[1][3]);

	__m256d m30 = _mm256_set1_pd(m->m[3][0]);
	__m256d m31 = _mm256_set1_pd(m->m[3][1]);
	__m256d m32 = _mm256_set1_pd(m->m[3][2]);
	__m256d m33 = _mm256_set1_pd(m->m[3][3]);

	/* 3. Center/Scale Adjustments */
	t_vec3d eff_center = cam->grid_center;
	eff_center.z *= cam->z_scale;
	__m256d cx = _mm256_set1_pd(eff_center.x);
	__m256d cy = _mm256_set1_pd(eff_center.y);
	__m256d cz = _mm256_set1_pd(eff_center.z);
	__m256d z_scale = _mm256_set1_pd(cam->z_scale);
	
	/* 4. Offsets */
	__m256d off_x = _mm256_set1_pd(cam->offset.x);
	__m256d off_y = _mm256_set1_pd(cam->offset.y);

	/* 5. Culling Thresholds */
	// We check if points are valid (z > BAD_VALUE + 1.0)
	// We can use vector comparison later, but strict equivalence with scalar is safer for BAD_VALUE.
	// Actually, let's just process normally and mask? No, complex.
	// Let's rely on standard loop for remainder and SIMD for bulk.
	// NOTE: Input data might contain BAD_VALUE. We must be careful not to create NaNs if possible, 
	// or just let them propagate and check result? 
	// Standard loop checked `in_pos[idx].z > BAD_VALUE`. 
	
	i = 0;
	while (i < width - 3)
	{
		size_t idx = row_idx + i;

		/* Check validity of 4 points scalarly (Branch prediction handles this well if coherent) */
		// If mostly valid (which is true for maps), this is fine.
		// If we encounter gaps, we might want to skip SIMD or mask.
		// For FDF maps, points are usually all valid or invalid (holes).
		// Let's load effectively.
		
		// Load 4 points (AoS). 
		// Structure: x0 y0 z0 | x1 y1 z1 | x2 y2 z2 | x3 y3 z3
		double *ptr = (double *)&in_pos[idx];
		
		/* De-interleave Logic:
		   Use set_pd to load specific doubles into vectors.
		*/
		
		// r0: [x0, y0, z0, x1]
		// r1: [y1, z1, x2, y2]
		// r2: [z2, x3, y3, z3]
		
		// Extract Xs:
		// x0 from r0[0]
		// x1 from r0[3]
		// x2 from r1[2]
		// x3 from r2[1]
		// Blend is painful for this pattern.
		
		// Optimized Scalar Load for Register Fill might be faster than complex shuffle?
		__m256d vx = _mm256_set_pd(ptr[9], ptr[6], ptr[3], ptr[0]); // x3, x2, x1, x0 (Reverse order for correct index mapping 3,2,1,0)
		__m256d vy = _mm256_set_pd(ptr[10], ptr[7], ptr[4], ptr[1]);
		__m256d vz = _mm256_set_pd(ptr[11], ptr[8], ptr[5], ptr[2]);
		
		// Prepare Model Space: v.x - cx ...
		vz = _mm256_mul_pd(vz, z_scale); // z * z_scale
		
		__m256d dx = _mm256_sub_pd(vx, cx);
		__m256d dy = _mm256_sub_pd(vy, cy);
		__m256d dz = _mm256_sub_pd(vz, cz);
		
		// Transform (MVP):
		// res_x = dx*m00 + dy*m01 + dz*m02 + m03
		__m256d res_x = _mm256_fmadd_pd(dx, m00, _mm256_fmadd_pd(dy, m01, _mm256_fmadd_pd(dz, m02, m03)));
		__m256d res_y = _mm256_fmadd_pd(dx, m10, _mm256_fmadd_pd(dy, m11, _mm256_fmadd_pd(dz, m12, m13)));
		__m256d res_w = _mm256_fmadd_pd(dx, m30, _mm256_fmadd_pd(dy, m31, _mm256_fmadd_pd(dz, m32, m33)));
		
		// Perspective Divide
		__m256d ones = _mm256_set1_pd(1.0);
		// Check for W != 0? DIV by 0 gives Inf, which is handled or clipped later.
		// Usually W is > near_plane.
		__m256d inv_w = _mm256_div_pd(ones, res_w);
		res_x = _mm256_mul_pd(res_x, inv_w);
		res_y = _mm256_mul_pd(res_y, inv_w);
		
		// Screen Offset
		res_x = _mm256_add_pd(res_x, off_x);
		res_y = _mm256_add_pd(res_y, off_y);
		
		// Calculate Z (View Space)
		// z = dx*rot0 + dy*rot1 + dz*rot2 - view_dist
		__m256d final_z = _mm256_fmadd_pd(dx, rot0, _mm256_fmadd_pd(dy, rot1, _mm256_fmadd_pd(dz, rot2, _mm256_setzero_pd())));
		final_z = _mm256_sub_pd(final_z, vdist);
		
		// Validity Check (BAD_VALUE)
		// scalar check again? Or store BAD if input was BAD?
		// We trust user data mostly.
		// If input Z was BAD_VALUE, 'vz' would be bad. 
		// For now store results.
		
		// Store results (Structure of Arrays -> Array of Structs)
		// We have 4x X, 4x Y, 4x Z. We need to write to `t_point *out`.
		// `t_point` is `pos` (3 doubles) + `color` (int/padding).
		// Sizeof t_point = 24 + 4 + 4(padding) = 32 bytes.
		// Ideally we write directly.
		
		double buf_x[4], buf_y[4], buf_z[4];
		_mm256_storeu_pd(buf_x, res_x);
		_mm256_storeu_pd(buf_y, res_y);
		_mm256_storeu_pd(buf_z, final_z);
		
		// Loop unroll store
		int k = 0;
		while (k < 4)
		{
			out[idx + k].pos.x = buf_x[k];
			out[idx + k].pos.y = buf_y[k];
			out[idx + k].pos.z = buf_z[k];
			out[idx + k].color = in_col[idx + k];
			
			// Optional: Restore validity check?
			// If input was BAD_VALUE, projected might be nonsense.
			// Let's keep original safe check?
			if (in_pos[idx + k].z <= BAD_VALUE + 1.0)
				out[idx + k].pos = create_vec3d(BAD_VALUE, BAD_VALUE, BAD_VALUE);

			k++;
		}
		
		i += 4;
	}

	/* Handle Remainder scalars */
	while (i < width)
	{
		size_t idx = row_idx + i;
		if (in_pos[idx].z > BAD_VALUE + 1.0)
		{
			t_point p = {in_pos[idx], in_col[idx]};
			out[idx] = apply_transform(p, cam);
		}
		else
			out[idx].pos = create_vec3d(BAD_VALUE, BAD_VALUE, BAD_VALUE);
		i++;
	}
}
