/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:29:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static bool	fbx_bin_set_vertices(t_fbx_bin *fbx)
{
	t_vec3		*v;
	size_t		i;

	v = repack_doubles_to_vec3((double *)fbx->data.v, fbx->data.vc);
	free(fbx->data.v);
	fbx->data.v = NULL;
	if (!v)
		return (false);
	fbx->mesh.base.vertices = ft_calloc(fbx->data.vc, sizeof(t_vertex));
	if (!fbx->mesh.base.vertices)
	{
		free(v);
		return (false);
	}
	i = 0;
	while (i < fbx->data.vc)
	{
		fbx->mesh.base.vertices[i].pos = v[i];
		i++;
	}
	fbx->mesh.base.vertex_count = fbx->data.vc;
	free(v);
	return (true);
}

static void	fbx_bin_set_normals(t_fbx_bin *fbx)
{
	t_vec3	*rn;

	if (!fbx->data.vn)
		return ;
	rn = repack_doubles_to_vec3((double *)fbx->data.vn, fbx->data.nc);
	free(fbx->data.vn);
	fbx->data.vn = rn;
}

static void	fbx_bin_fill_params(t_fbx_flat_params *p, t_fbx_data *d)
{
	p->raw = d->ri;
	p->raw_c = d->rc;
	p->n = d->vn;
	p->nc = d->nc;
	p->u = d->vu;
	p->uc = d->uc;
	p->vc = d->vc;
}

static void	fbx_bin_release_arrays(t_fbx_bin *fbx)
{
	if (fbx->data.vn)
		free(fbx->data.vn);
	if (fbx->data.vu)
		free(fbx->data.vu);
	if (fbx->data.ri)
		free(fbx->data.ri);
}

bool	fbx_bin_build_mesh(t_fbx_bin *fbx)
{
	t_fbx_flat_params	p;

	if (!fbx_bin_set_vertices(fbx))
		return (false);
	fbx_bin_set_normals(fbx);
	fbx_bin_fill_params(&p, &fbx->data);
	ft_print_debug("DEBUG: calling fbx_build_flat\n");
	fbx_build_flat(&fbx->mesh.base, &p);
	ft_print_debug("DEBUG: fbx_build_flat finished\n");
	fbx_bin_release_arrays(fbx);
	if (fbx->mesh.base.tri_count == 0)
		return (false);
	mesh_build_bvh(&fbx->mesh.base);
	return (true);
}
