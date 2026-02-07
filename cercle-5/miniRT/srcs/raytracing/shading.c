/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 03:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	is_in_shadow(t_scene *scene, const t_bvh *bvh, t_vec3 point, t_vec3 light_dir, double light_dist)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit = {0};
	int		i;

	// Offset to prevent self-intersection (Shadow Acne fix)
	shadow_ray.origin = point;
	shadow_ray.direction = light_dir;

	if (bvh_intersect(bvh, &shadow_ray, &shadow_hit))
	{
		if (shadow_hit.t < light_dist)
			return (true);
	}

	// Check planes (Infinite BVH fix)
	for (i = 0; i < scene->plane_count; i++)
	{
		if (intersect_plane(&shadow_ray, &scene->planes[i], &shadow_hit))
		{
			if (shadow_hit.t > 1e-4 && shadow_hit.t < light_dist)
				return (true);
		}
	}
	return (false);
}

static t_vec3	pixel_color(t_vec3 obj_color, t_vec3 light_color, double intensity)
{
	t_vec3	final;

	final.x = (obj_color.x / 255.0) * (light_color.x / 255.0) * intensity * 255.0;
	final.y = (obj_color.y / 255.0) * (light_color.y / 255.0) * intensity * 255.0;
	final.z = (obj_color.z / 255.0) * (light_color.z / 255.0) * intensity * 255.0;
	
	// Clamp to 255
	if (final.x > 255) final.x = 255;
	if (final.y > 255) final.y = 255;
	if (final.z > 255) final.z = 255;
	return (final);
}

t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh, const t_ray *ray, int depth)
{
	t_vec3		total_color;
	t_vec3		ambient;
	t_material	mat;
	int			i;

	(void)depth; // No recursion for now
	
	// Retrieve material
	if (hit->ref.type == TYPE_SPHERE) mat = scene->materials[scene->spheres[hit->ref.index].mat_id];
	else if (hit->ref.type == TYPE_PLANE) mat = scene->materials[scene->planes[hit->ref.index].mat_id];
	else if (hit->ref.type == TYPE_CYLINDER) mat = scene->materials[scene->cylinders[hit->ref.index].mat_id];
	else if (hit->ref.type == TYPE_CONE) mat = scene->materials[scene->cones[hit->ref.index].mat_id];
	else return (vec3(255, 0, 255)); // Error pink

	// Albedo (Texture/Color/Checker)
	mat.albedo_map.type = (mat.albedo_map.type == 0) ? TEX_SOLID : mat.albedo_map.type; // Safety default
	t_vec3 albedo_color = sample_texture(&mat.albedo_map, hit->u, hit->v);

	// Bump Map (Normal Mapping)
	if (mat.bump_map.type != TEX_SOLID && mat.bump_map.img)
	{
		t_vec3 bump_sample = sample_texture(&mat.bump_map, hit->u, hit->v);
		
		// Map [0, 255] to [-1, 1]
		t_vec3 map_n;
		map_n.x = (bump_sample.x / 255.0) * 2.0 - 1.0;
		map_n.y = (bump_sample.y / 255.0) * 2.0 - 1.0;
		map_n.z = (bump_sample.z / 255.0) * 2.0 - 1.0; // Usually Z is up in normal maps [0,1] mapped to [0,1]? 
		// Actually standard OpenGL normal maps: Z ranges [0.5, 1.0] -> [0, 1]. 
		// If map_n.z is 128 (0.5), it means 0? No, flat normal is (0.5, 0.5, 1.0) RGB -> (0, 0, 1) Vector.
		// So formula is correct: (val / 255) * 2 - 1.
		
		// TBN Transform: WorldN = T * map.x + B * map.y + N * map.z
		t_vec3 new_normal;
		new_normal.x = hit->tangent.x * map_n.x + hit->bitangent.x * map_n.y + hit->normal.x * map_n.z;
		new_normal.y = hit->tangent.y * map_n.x + hit->bitangent.y * map_n.y + hit->normal.y * map_n.z;
		new_normal.z = hit->tangent.z * map_n.x + hit->bitangent.z * map_n.y + hit->normal.z * map_n.z;
		
		hit->normal = vec3_norm(new_normal);
	}

	// Ambient
	ambient = pixel_color(albedo_color, scene->ambient.rgb, scene->ambient.brightness);
	total_color = ambient;

	// Loop Lights
	for (i = 0; i < scene->light_count; i++)
	{
		t_light light = scene->lights[i];
		t_vec3	light_dir = vec3_sub(light.pos, hit->point);
		double	light_dist = vec3_mag(light_dir);
		light_dir = vec3_norm(light_dir); // Normalize

		// Optimize: Check if face is facing the light
		double ndotl = vec3_dot(hit->normal, light_dir);
		if (ndotl <= 0.0)
			continue ;

		// Spot Light Check
		if (light.type == LIGHT_SPOT)
		{
			// light.dir is direction OF the light
			// Vector from light to point is -light_dir (calculated above as light_dir = Norm(L - P)) 
			// Wait, light_dir = vec3_norm(vec3_sub(light.pos, hit->point)); -> Point TO Light
			// So vector from Light TO Point is -light_dir.
			
			t_vec3 l_to_p = vec3_scale(light_dir, -1.0);
			double angle = vec3_dot(l_to_p, light.dir); // light.dir should be normalized
			
			if (angle < light.cutoff) // cos(angle) < cos(cutoff) -> angle > cutoff (if both positive)
				continue ;
		}

		// Shadow Check
		// Epsilon offset along normal to avoid self-acne
		t_vec3 shadow_origin = vec3_add(hit->point, vec3_scale(hit->normal, 1e-4));
		if (is_in_shadow(scene, bvh, shadow_origin, light_dir, light_dist))
			continue ;

		// Diffuse (Lambert)
		t_vec3 diffuse = pixel_color(albedo_color, light.rgb, light.brightness * ndotl);
		total_color = vec3_add(total_color, diffuse);

		// Specular (Blinn-Phong)
		t_vec3 view_dir = vec3_scale(ray->direction, -1.0); // View is opposite to ray

		t_vec3 half_dir = vec3_norm(vec3_add(light_dir, view_dir));
		double spec_angle = fmax(0.0, vec3_dot(hit->normal, half_dir));
		double specular_factor = pow(spec_angle, mat.shininess);
		
		// Specular color defines the color of the highlight (usually white or light color)
		// We use light color * mat.specular (intensity)
		t_vec3 specular = vec3_scale(light.rgb, light.brightness * mat.specular * specular_factor);
		total_color = vec3_add(total_color, specular);
	}

	// Clamp final
	if (total_color.x > 255) total_color.x = 255;
	if (total_color.y > 255) total_color.y = 255;
	if (total_color.z > 255) total_color.z = 255;
	
	return (total_color);
}
