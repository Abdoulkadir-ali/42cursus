/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

static t_tri_shape	make_tri(t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 col)
{
	t_tri_shape	tr;
	t_vec3		e1;
	t_vec3		e2;

	ft_memset(&tr, 0, sizeof(tr));
	tr.v[0] = a;
	tr.v[1] = b;
	tr.v[2] = c;
	tr.temp_color = col;
	e1 = vec3_sub(b, a);
	e2 = vec3_sub(c, a);
	tr.normal = vec3_norm(vec3_cross(e1, e2));
	return (tr);
}

static bool	process_rect(t_scene *sc, t_rect_parse *r)
{
	if (!scene_add_tri(sc, make_tri(r->v[0], r->v[1], r->v[2], r->temp_color)))
		return (false);
	return (scene_add_tri(sc,
			make_tri(r->v[0], r->v[2], r->v[3], r->temp_color)));
}

static void	pyramid_base(t_pyramid_parse *py, t_vec3 c[4], t_vec3 *apex)
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	c[0] = vec3_add(vec3_add(py->center, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	c[1] = vec3_add(vec3_add(py->center, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	c[2] = vec3_add(vec3_add(py->center, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	c[3] = vec3_add(vec3_add(py->center, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
	*apex = vec3_add(py->center, vec3_scale(py->up, py->height));
}

static bool	process_pyramid(t_scene *sc, t_pyramid_parse *py)
{
	t_vec3	c[4];
	t_vec3	apex;
	t_vec3	col;

	col = py->temp_color;
	pyramid_base(py, c, &apex);
	if (!scene_add_tri(sc, make_tri(c[0], c[1], c[2], col)))
		return (false);
	if (!scene_add_tri(sc, make_tri(c[0], c[2], c[3], col)))
		return (false);
	if (!scene_add_tri(sc, make_tri(c[0], c[1], apex, col)))
		return (false);
	if (!scene_add_tri(sc, make_tri(c[1], c[2], apex, col)))
		return (false);
	if (!scene_add_tri(sc, make_tri(c[2], c[3], apex, col)))
		return (false);
	return (scene_add_tri(sc, make_tri(c[3], c[0], apex, col)));
}

static bool	process_polygon(t_scene *sc, t_parse_obj *obj)
{
	if (obj->type == TYPE_TRI)
		return (scene_add_tri(sc, obj->data.tri_shape));
	if (obj->type == TYPE_RECT)
		return (process_rect(sc, &obj->data.rect_parse));
	if (obj->type == TYPE_PYRAMID)
		return (process_pyramid(sc, &obj->data.pyramid_parse));
	return (false);
}

static bool	process_mesh_object(t_scene *scene, t_parse_obj *obj)
{
	const char	*ext;
	bool		ret;

	ext = ft_strrchr(obj->data.mesh_info.path, '.');
	ret = handle_mesh_injection(obj, ext, scene);
	free(obj->data.mesh_info.path);
	return (ret);
}

bool	process_object(t_scene *scene, t_parse_obj obj)
{
	if (obj.type == TYPE_SPHERE)
		return (scene_add_sphere(scene, obj.data.sphere));
	if (obj.type == TYPE_PLANE)
		return (scene_add_plane(scene, obj.data.plane));
	if (obj.type == TYPE_CYLINDER)
		return (scene_add_cylinder(scene, obj.data.cylinder));
	if (obj.type == TYPE_CONE)
		return (scene_add_cone(scene, obj.data.cone));
	if (obj.type == TYPE_LIGHT)
		return (scene_add_light(scene, obj.data.light));
	if (obj.type == TYPE_CAMERA)
	{
		scene->camera = obj.data.camera;
		return (true);
	}
	if (obj.type == TYPE_AMBIENT)
	{
		scene->ambient = obj.data.ambient;
		return (true);
	}
	if (obj.type == TYPE_ANIM || obj.type == TYPE_MESH)
		return (process_mesh_object(scene, &obj));
	if (obj.type == TYPE_TRI || obj.type == TYPE_RECT
		|| obj.type == TYPE_PYRAMID)
		return (process_polygon(scene, &obj));
	return (true);
}
