/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:36:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	write_color(FILE *f, t_vec3 c)
{
	fprintf(f, "%d,%d,%d",
		(int)(ft_clampf(c.x, 0, 1) * 255 + 0.5f),
		(int)(ft_clampf(c.y, 0, 1) * 255 + 0.5f),
		(int)(ft_clampf(c.z, 0, 1) * 255 + 0.5f));
}

static void	write_mat(FILE *f, const t_material *m)
{
	if (m->roughness != 0.6f)
		fprintf(f, "    rough %.3f\n", m->roughness);
	if (m->metallic > 0.0f)
		fprintf(f, "    metal %.3f\n", m->metallic);
	if (m->reflectivity > 0.0f)
		fprintf(f, "    refl %.3f\n", m->reflectivity);
	if (m->opacity < 1.0f)
	{
		fprintf(f, "    opac %.3f\n", m->opacity);
		fprintf(f, "    ior %.3f\n", m->ior);
	}
	if (m->emit_power > 0.0f)
	{
		fprintf(f, "    emit ");
		write_color(f, m->emit_color);
		fprintf(f, "\n    emit_power %.1f\n", m->emit_power);
	}
	if (m->name[0])
		fprintf(f, "    name %s\n", m->name);
}

static void	write_header(FILE *f, const t_scene *s)
{
	fprintf(f, "A %.3f ", s->amb.ratio);
	write_color(f, s->amb.color);
	fprintf(f, "\nC %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.1f\n\n",
		s->cam.pos.x, s->cam.pos.y, s->cam.pos.z,
		s->cam.dir.x, s->cam.dir.y, s->cam.dir.z, s->cam.fov);
}

static void	write_lights(FILE *f, const t_scene *s)
{
	size_t	i;

	i = 0;
	while (i < s->n_lights)
	{
		fprintf(f, "L %.3f,%.3f,%.3f %.3f ",
			s->lights[i].pos.x, s->lights[i].pos.y, s->lights[i].pos.z,
			s->lights[i].ratio);
		write_color(f, s->lights[i].color);
		fputc('\n', f);
		i++;
	}
	fprintf(f, "\n");
}

static void	write_planes(FILE *f, const t_scene *s)
{
	const t_object	*o;
	size_t			i;

	i = 0;
	while (i < s->n_planes)
	{
		o = &s->planes[i++];
		fprintf(f, "pl %.3f,%.3f,%.3f %.3f,%.3f,%.3f ",
			o->u.pln.point.x, o->u.pln.point.y, o->u.pln.point.z,
			o->u.pln.normal.x, o->u.pln.normal.y, o->u.pln.normal.z);
		write_color(f, o->color);
		fputc('\n', f);
		write_mat(f, &o->mat);
	}
}

static void	write_obj_geom(FILE *f, const t_object *o)
{
	if (o->type == OBJ_SPHERE)
		fprintf(f, "sp %.3f,%.3f,%.3f %.3f ",
			o->u.sph.center.x, o->u.sph.center.y, o->u.sph.center.z,
			o->u.sph.radius * 2.0f);
	else if (o->type == OBJ_CYLINDER)
		fprintf(f, "cy %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.3f %.3f ",
			o->u.cyl.base.x, o->u.cyl.base.y, o->u.cyl.base.z,
			o->u.cyl.axis.x, o->u.cyl.axis.y, o->u.cyl.axis.z,
			o->u.cyl.radius * 2.0f, o->u.cyl.height);
	else if (o->type == OBJ_BOX)
		fprintf(f, "bx %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.3f,%.3f,%.3f ",
			o->u.box.center.x, o->u.box.center.y, o->u.box.center.z,
			o->u.box.u.x, o->u.box.u.y, o->u.box.u.z,
			o->u.box.he.x * 2.0f, o->u.box.he.y * 2.0f, o->u.box.he.z * 2.0f);
	else if (o->type == OBJ_CAPSULE)
		fprintf(f, "ca %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.3f %.3f ",
			o->u.cap.base.x, o->u.cap.base.y, o->u.cap.base.z,
			o->u.cap.axis.x, o->u.cap.axis.y, o->u.cap.axis.z,
			o->u.cap.radius * 2.0f, o->u.cap.height);
	else if (o->type == OBJ_PYRAMID)
		fprintf(f, "py %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.3f %.3f ",
			o->u.pyr.base.x, o->u.pyr.base.y, o->u.pyr.base.z,
			o->u.pyr.axis.x, o->u.pyr.axis.y, o->u.pyr.axis.z,
			o->u.pyr.side, o->u.pyr.height);
	else if (o->type == OBJ_TRIANGLE)
		fprintf(f, "tr %.3f,%.3f,%.3f %.3f,%.3f,%.3f %.3f,%.3f,%.3f ",
			o->u.tri.a.x, o->u.tri.a.y, o->u.tri.a.z,
			o->u.tri.b.x, o->u.tri.b.y, o->u.tri.b.z,
			o->u.tri.c.x, o->u.tri.c.y, o->u.tri.c.z);
}

static void	write_bvh_objs(FILE *f, const t_scene *s)
{
	const t_object	*o;
	size_t			i;

	i = 0;
	while (i < s->n_bvh)
	{
		o = &s->bvh_objs[i++];
		write_obj_geom(f, o);
		write_color(f, o->color);
		fputc('\n', f);
		write_mat(f, &o->mat);
	}
}

int	scene_save(const t_scene *s, const char *path)
{
	FILE	*f;

	f = fopen(path, "w");
	if (!f)
		return (-1);
	write_header(f, s);
	write_lights(f, s);
	write_planes(f, s);
	write_bvh_objs(f, s);
	fclose(f);
	return (0);
}