/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 16:15:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static bool	fbx_bin_set_vertices(t_fbx_bin *fbx)
{
	t_vec3		*v;
	size_t		i;

	v = repack_doubles_to_vec3((double *)fbx->data.v, fbx->data.rv.y);
	free(fbx->data.v);
	fbx->data.v = NULL;
	if (!v)
		return (false);
	fbx->mesh.base.vertices = ft_calloc(fbx->data.rv.y, sizeof(t_vertex));
	if (!fbx->mesh.base.vertices)
	{
		free(v);
		return (false);
	}
	i = 0;
	while (i < fbx->data.rv.y)
	{
		fbx->mesh.base.vertices[i].pos = v[i];
		i++;
	}
	fbx->mesh.base.vertex_count = fbx->data.rv.y;
	free(v);
	return (true);
}

static void	fbx_bin_set_normals(t_fbx_bin *fbx)
{
	t_vec3	*rn;

	if (!fbx->data.vn)
		return ;
	rn = repack_doubles_to_vec3((double *)fbx->data.vn, fbx->data.nu.x);
	free(fbx->data.vn);
	fbx->data.vn = rn;
}

static void	fbx_bin_fill_params(t_fbx_flat_params *p, t_fbx_data *d)
{
	p->raw = d->ri;
	p->rv.x = d->rv.x;
	p->n = d->vn;
	p->nu.x = d->nu.x;
	p->u = d->vu;
	p->nu.y = d->nu.y;
	p->rv.y = d->rv.y;
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
	ft_print_debug("[MESH] vc=%zu rc=%zu nc=%zu uc=%zu\n",
		fbx->data.rv.y, fbx->data.rv.x, fbx->data.nu.x, fbx->data.nu.y);
	if (fbx->data.ri)
	{
		ft_print_debug("[MESH] ri[0..7]: %d %d %d %d %d %d %d %d\n",
			fbx->data.ri[0], fbx->data.ri[1], fbx->data.ri[2], fbx->data.ri[3],
			fbx->data.ri[4], fbx->data.ri[5], fbx->data.ri[6], fbx->data.ri[7]);
	}
	ft_print_debug("DEBUG: calling fbx_build_flat\n");
	fbx_build_flat(&fbx->mesh.base, &p);
	ft_print_debug("DEBUG: fbx_build_flat finished\n");
	fbx_bin_release_arrays(fbx);
	if (fbx->mesh.base.tri_count == 0)
		return (false);
	mesh_build_bvh(&fbx->mesh.base);
	return (true);
}
