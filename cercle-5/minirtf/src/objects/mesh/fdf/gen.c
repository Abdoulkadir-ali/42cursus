/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:08:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:51:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "fdf.h"

static void	get_verts(t_vec3 *v, t_vec2i ij, t_fdf_grid *g, t_mesh_conf *c)
{
	t_vec2	x;
	t_vec2	y;

	x.x = (ij.y - (g->w - 1) * 0.5f) * c->scale + c->origin.x;
	x.y = (ij.y + 1 - (g->w - 1) * 0.5f) * c->scale + c->origin.x;
	y.x = (ij.x - (g->h - 1) * 0.5f) * c->scale + c->origin.z;
	y.y = (ij.x + 1 - (g->h - 1) * 0.5f) * c->scale + c->origin.z;
	v[0] = (t_vec3){x.x, c->origin.y + g->z[ij.x * g->w + ij.y] * c->zscale,
		y.x};
	v[1] = (t_vec3){x.y, c->origin.y + g->z[ij.x * g->w + ij.y + 1]
		* c->zscale, y.x};
	v[2] = (t_vec3){x.x, c->origin.y + g->z[(ij.x + 1) * g->w + ij.y]
		* c->zscale, y.y};
	v[3] = (t_vec3){x.y, c->origin.y + g->z[(ij.x + 1) * g->w + ij.y + 1]
		* c->zscale, y.y};
}

int	fdf_gen_mesh(t_scene *s, t_fdf_grid *g, t_mesh_conf *c)
{
	t_vec2i	ij;
	t_vec3	v[4];
	t_vec3	tri[3];

	ij.x = 0;
	while (ij.x < g->h - 1)
	{
		ij.y = 0;
		while (ij.y < g->w - 1)
		{
			get_verts(v, ij, g, c);
			tri[0] = v[0];
			tri[1] = v[1];
			tri[2] = v[3];
			if (fdf_push_tri(s, tri, c->color) < 0)
				return (-1);
			tri[1] = v[3];
			tri[2] = v[2];
			if (fdf_push_tri(s, tri, c->color) < 0)
				return (-1);
			ij.y++;
		}
		ij.x++;
	}
	return (0);
}
