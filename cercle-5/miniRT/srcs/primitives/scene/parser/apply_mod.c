/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:08:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/* ---- per-type accessors ---- */

typedef struct s_obj_mat_ref
{
	size_t	*mat_id;
	size_t	*mat_slots;
	int		*active_slot;
}	t_obj_mat_ref;

static bool	get_last_obj_ref(t_scene *sc, t_type type, t_obj_mat_ref *out)
{
	if (type == TYPE_SPHERE && sc->sphere_count > 0)
	{
		t_sphere *o = &sc->spheres[sc->sphere_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_PLANE && sc->plane_count > 0)
	{
		t_plane *o = &sc->planes[sc->plane_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_CYLINDER && sc->cylinder_count > 0)
	{
		t_cylinder *o = &sc->cylinders[sc->cylinder_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_CONE && sc->cone_count > 0)
	{
		t_cone *o = &sc->cones[sc->cone_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_TRI && sc->tri_count > 0)
	{
		t_tri_shape *o = &sc->tris[sc->tri_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_RECT && sc->rect_count > 0)
	{
		t_rect *o = &sc->rects[sc->rect_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_PYRAMID && sc->pyramid_count > 0)
	{
		t_pyramid *o = &sc->pyramids[sc->pyramid_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_BOX && sc->box_count > 0)
	{
		t_box *o = &sc->boxes[sc->box_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_CAPSULE && sc->capsule_count > 0)
	{
		t_capsule *o = &sc->capsules[sc->capsule_count - 1];
		out->mat_id = &o->mat_id; out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot; return (true);
	}
	if (type == TYPE_MESH && sc->mesh_count > 0)
	{
		t_mesh	*o = &sc->meshes[sc->mesh_count - 1];
		out->mat_id = &o->mat_id;
		out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot;
		return (true);
	}
	if (type == TYPE_ANIM && sc->anim_count > 0)
	{
		t_mesh	*o = &sc->animated[sc->anim_count - 1].base;
		out->mat_id = &o->mat_id;
		out->mat_slots = o->mat_slots;
		out->active_slot = &o->active_slot;
		return (true);
	}
	return (false);
}

/* ---- ensure private (cloned) material for current active slot ---- */

static size_t	ensure_private_mat(t_scene *sc, t_obj_mat_ref *ref,
		bool *cloned)
{
	t_index	cl;
	size_t	cur;

	cur = ref->mat_slots[*ref->active_slot];
	if (*cloned)
		return (cur);
	cl = scene_clone_material(sc, cur);
	if (cl.error)
		return (cur);
	ref->mat_slots[*ref->active_slot] = cl.i;
	*ref->mat_id = cl.i;
	*cloned = true;
	return (cl.i);
}

/* ---- apply one property to material ---- */

static void	apply_property(t_material *mat, t_mat_mod *mod)
{
	if (mod->kind == MAT_MOD_ROUGHNESS)
		mat->roughness = mod->val;
	else if (mod->kind == MAT_MOD_METALLIC)
		mat->metallic = mod->val;
	else if (mod->kind == MAT_MOD_EMISSION)
		mat->emission = mod->color_a;
	else if (mod->kind == MAT_MOD_OPACITY)
		mat->transparency = 1.0 - mod->val;
	else if (mod->kind == MAT_MOD_REFLECTIVITY)
		mat->reflectivity = mod->val;
	else if (mod->kind == MAT_MOD_IOR)
		mat->refract_index = mod->val;
	else if (mod->kind == MAT_MOD_SHININESS)
		mat->shininess = mod->val;
	else if (mod->kind == MAT_MOD_UV_SCALE)
		mat->albedo_map.scale = mod->val;
	else if (mod->kind == MAT_MOD_EMIT_POWER)
	{
		mat->emission.x *= mod->val;
		mat->emission.y *= mod->val;
		mat->emission.z *= mod->val;
	}
	else if (mod->kind == MAT_MOD_NAME)
	{
		free(mat->name);
		mat->name = ft_strdup(mod->path);
	}
}

/* ---- handle mat s/c/t ---- */

static void	apply_mat_type(t_scene *sc, t_obj_mat_ref *ref,
		t_mat_mod *mod, bool *cloned)
{
	t_index	id;

	if (mod->kind == MAT_MOD_SOLID)
	{
		id = scene_add_fresh_material(sc, mod->color_a);
		if (!id.error)
		{
			ref->mat_slots[0] = id.i;
			*ref->mat_id = id.i;
			*ref->active_slot = 0;
			*cloned = true;
		}
	}
	else if (mod->kind == MAT_MOD_CHECKER)
	{
		size_t cid = scene_add_checker_material(sc, mod->color_a,
				mod->color_b, mod->scale > 0.0 ? mod->scale : 1.0);
		ref->mat_slots[1] = cid;
		*ref->mat_id = cid;
		*ref->active_slot = 1;
		*cloned = true;
	}
	else if (mod->kind == MAT_MOD_TEXTURE)
	{
		id = scene_add_fresh_material(sc, vec3(255, 255, 255));
		if (!id.error && mod->path[0] != '\0')
		{
			if (!sc->mlx || load_texture(sc->mlx, &sc->materials[id.i].albedo_map,
					mod->path))
			{
				ref->mat_slots[3] = id.i;
				*ref->mat_id = id.i;
				*ref->active_slot = 3;
				*cloned = true;
			}
		}
	}
	else if (mod->kind == MAT_MOD_BUMP)
	{
		size_t	bid;

		bid = ensure_private_mat(sc, ref, cloned);
		if (bid < sc->mat_count && mod->path[0] != '\0' && sc->mlx)
			load_texture(sc->mlx, &sc->materials[bid].bump_map, mod->path);
	}
}

/* ---- physics modifier — mesh/anim only ---- */

static void	apply_phys_mod(t_scene *sc, t_mat_mod *mod, t_type last_type)
{
	t_mesh	*m;

	if (last_type == TYPE_MESH && sc->mesh_count > 0)
		m = &sc->meshes[sc->mesh_count - 1];
	else if (last_type == TYPE_ANIM && sc->anim_count > 0)
		m = &sc->animated[sc->anim_count - 1].base;
	else
		return ;
	if (mod->kind == MAT_MOD_PHYS_MASS)
	{
		m->phys.mass = mod->val;
		if (mod->val > 0.0)
			m->phys.inv_mass = 1.0 / mod->val;
		else
			m->phys.inv_mass = 0.0;
	}
	else if (mod->kind == MAT_MOD_PHYS_STATIC)
		m->phys.is_static = (mod->val != 0.0);
	else if (mod->kind == MAT_MOD_PHYS_ELAST)
		m->phys.elasticity = mod->val;
	else if (mod->kind == MAT_MOD_PHYS_FRIC)
		m->phys.friction = mod->val;
}

/* ---- public entry point ---- */

void	apply_mat_mod_to_last(t_scene *scene, t_rt *rt, t_mat_mod *mod)
{
	t_obj_mat_ref	ref;
	size_t			mat_id;

	if (rt->last_type == TYPE_NONE)
		return ;
	if (mod->kind == MAT_MOD_PHYS_MASS || mod->kind == MAT_MOD_PHYS_STATIC
		|| mod->kind == MAT_MOD_PHYS_ELAST || mod->kind == MAT_MOD_PHYS_FRIC)
	{
		apply_phys_mod(scene, mod, rt->last_type);
		return ;
	}
	if (!get_last_obj_ref(scene, rt->last_type, &ref))
		return ;
	if (mod->kind == MAT_MOD_SOLID || mod->kind == MAT_MOD_CHECKER
		|| mod->kind == MAT_MOD_TEXTURE || mod->kind == MAT_MOD_BUMP)
	{
		apply_mat_type(scene, &ref, mod, &rt->last_mat_cloned);
		return ;
	}
	mat_id = ensure_private_mat(scene, &ref, &rt->last_mat_cloned);
	if (mat_id >= scene->mat_count)
		return ;
	apply_property(&scene->materials[mat_id], mod);
}
