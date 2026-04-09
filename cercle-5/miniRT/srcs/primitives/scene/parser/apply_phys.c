/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_phys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static t_physics_body	*get_phys_basic(t_scene *sc, t_type type)
{
	if (type == TYPE_SPHERE && sc->sphere_count > 0)
		return (&sc->spheres[sc->sphere_count - 1].phys);
	if (type == TYPE_PLANE && sc->plane_count > 0)
		return (&sc->planes[sc->plane_count - 1].phys);
	if (type == TYPE_CYLINDER && sc->cylinder_count > 0)
		return (&sc->cylinders[sc->cylinder_count - 1].phys);
	if (type == TYPE_CONE && sc->cone_count > 0)
		return (&sc->cones[sc->cone_count - 1].phys);
	if (type == TYPE_TRI && sc->tri_count > 0)
		return (&sc->tris[sc->tri_count - 1].phys);
	return (NULL);
}

static t_physics_body	*get_phys_body(t_scene *sc, t_type type)
{
	t_physics_body	*res;

	res = get_phys_basic(sc, type);
	if (res)
		return (res);
	if (type == TYPE_RECT && sc->rect_count > 0)
		return (&sc->rects[sc->rect_count - 1].phys);
	if (type == TYPE_PYRAMID && sc->pyramid_count > 0)
		return (&sc->pyramids[sc->pyramid_count - 1].phys);
	if (type == TYPE_BOX && sc->box_count > 0)
		return (&sc->boxes[sc->box_count - 1].phys);
	if (type == TYPE_CAPSULE && sc->capsule_count > 0)
		return (&sc->capsules[sc->capsule_count - 1].phys);
	if (type == TYPE_MESH && sc->mesh_count > 0)
		return (&sc->meshes[sc->mesh_count - 1].phys);
	if (type == TYPE_ANIM && sc->anim_count > 0)
		return (&sc->animated[sc->anim_count - 1].base.phys);
	return (NULL);
}

void	apply_phys_mod(t_scene *sc, t_mat_mod *mod, t_type last_type)
{
	t_physics_body	*body;

	body = get_phys_body(sc, last_type);
	if (!body)
		return ;
	if (mod->kind == MAT_MOD_PHYS_MASS)
	{
		body->mass = mod->val;
		if (mod->val > 0.0)
			body->inv_mass = 1.0 / mod->val;
		else
			body->inv_mass = 0.0;
	}
	else if (mod->kind == MAT_MOD_PHYS_STATIC)
		body->is_static = (bool)mod->val;
	else if (mod->kind == MAT_MOD_PHYS_ELAST)
		body->elasticity = mod->val;
	else if (mod->kind == MAT_MOD_PHYS_FRIC)
		body->friction = mod->val;
	else if (mod->kind == MAT_MOD_PHYS_VEL)
		body->velocity = mod->color_a;
}
