/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 20:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "objects.h"

void	print_sphere(t_sphere *s)
{
	if (!s) return ;
	printf("sphere(\n  transform: ");
	print_transform(&s->transform);
	printf("\n  radius_sq: %.4f\n  mat_id: %d\n)", s->radius_sq, s->mat_id);
}

void	print_plane(t_plane *p)
{
	if (!p) return ;
	printf("plane(\n  transform: ");
	print_transform(&p->transform);
	printf("\n  mat_id: %d\n)", p->mat_id);
}

void	print_cylinder(t_cylinder *c)
{
	if (!c) return ;
	printf("cylinder(\n  transform: ");
	print_transform(&c->transform);
	printf("\n  mat_id: %d\n)", c->mat_id);
}

void	print_cone(t_cone *c)
{
	if (!c) return ;
	printf("cone(\n  transform: ");
	print_transform(&c->transform);
	printf("\n  mat_id: %d\n)", c->mat_id);
}

void	print_light(t_light *l)
{
	if (!l) return ;
	printf("light(\n  type: %s\n  transform: ", \
		l->type == LIGHT_POINT ? "POINT" : "SPOT");
	print_transform(&l->transform);
	printf("\n  brightness: %.4f\n  rgb: ", l->brightness);
	print_vec3(&l->rgb);
	printf("\n  cutoff: %.4f\n)", l->cutoff);
}

void	print_camera(t_camera *c)
{
	if (!c) return ;
	printf("camera(\n  transform: ");
	print_transform(&c->transform);
	printf("\n  fov: %.4f\n)", c->fov);
}

void	print_ambient(t_ambient *a)
{
	if (!a) return ;
	printf("ambient(\n  brightness: %.4f\n  rgb: ", a->brightness);
	print_vec3(&a->rgb);
	printf("\n)");
}

static void	print_texture(t_texture *t, char *name)
{
	char *types[] = {"SOLID", "CHECKER", "BITMAP", "BUMP"};
	if (!t) return ;
	printf("    %s: type: %s, color_a: ", name, types[t->type]);
	print_vec3(&t->color_a);
	printf(", color_b: ");
	print_vec3(&t->color_b);
	printf(", scale: %.4f\n", t->scale);
}

void	print_material(t_material *m)
{
	if (!m) return ;
	printf("material(\n");
	print_texture(&m->albedo_map, "albedo_map");
	print_texture(&m->bump_map, "bump_map");
	printf("    specular: %.4f, shininess: %.4f\n", m->specular, m->shininess);
	printf("    metallic: %.4f, roughness: %.4f\n", m->metallic, m->roughness);
	printf("    emission: ");
	print_vec3(&m->emission);
	printf("\n    refract_index: %.4f, transparency: %.4f, reflectivity: %.4f\n)", \
		m->refract_index, m->transparency, m->reflectivity);
}

void	print_mesh(t_mesh *m)
{
	if (!m) return ;
	printf("mesh(\n  name: %s\n  tri_count: %d\n  mat_id: %d\n  bbox: ", \
		m->name ? m->name : "NULL", m->tri_count, m->mat_id);
	print_aabb(&m->bbox);
	printf("\n  transform: ");
	print_transform(&m->transform);
	printf("\n)");
}

void	print_obj_ctx(t_obj_ctx *c)
{
	if (!c) return ;
	printf("obj_ctx(\n");
	printf("  temp_v: %zu/%zu, temp_vt: %zu/%zu, temp_vn: %zu/%zu\n", \
		c->v_count, c->v_cap, c->vt_count, c->vt_cap, c->vn_count, c->vn_cap);
	printf("  out_v: %zu/%zu, out_i: %zu/%zu\n", \
		c->out_v_count, c->out_v_cap, c->out_i_count, c->out_i_cap);
	printf("  bbox: ");
	print_aabb(&c->bbox);
	printf("\n)");
}
