/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:55:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static bool	alloc_vertex_data(t_mesh_asset *mesh, t_mesh_init init)
{
    if (init.v_count <= 0)
        return (true);
    mesh->vertices = malloc(sizeof(t_vec3) * init.v_count);
    if (!mesh->vertices)
        return (false);
    if (init.has_normals)
    {
        mesh->normals = malloc(sizeof(t_vec3) * init.v_count);
        if (!mesh->normals)
            return (false);
    }
    if (init.has_uvs)
    {
        mesh->uvs = malloc(sizeof(t_vec2) * init.v_count);
        if (!mesh->uvs)
            return (false);
    }
    return (true);
}

static bool	alloc_index_data(t_mesh_asset *mesh, t_mesh_init init)
{
    if (init.i_count <= 0)
        return (true);
    mesh->indices = malloc(sizeof(int) * init.i_count);
    if (!mesh->indices)
        return (false);
    return (true);
}

static void	mesh_base_init(t_mesh_asset *mesh)
{
    ft_memset(mesh, 0, sizeof(t_mesh_asset));
    mesh->transform.scale = vec3(1, 1, 1);
    mesh->group_id = -1;
}

bool	mesh_init(t_mesh_asset *mesh, t_mesh_init init)
{
    mesh_base_init(mesh);
    mesh->vertex_count = init.v_count;
    mesh->tri_count = init.i_count / 3;
    if (!alloc_vertex_data(mesh, init))
        return (mesh_free(mesh), false);
    if (!alloc_index_data(mesh, init))
        return (mesh_free(mesh), false);
    return (true);
}

void	init_mesh(t_mesh_asset *mesh, const char *path)
{
    mesh_base_init(mesh);
    if (path)
        mesh->name = ft_strdup(path);
    mesh->bbox = aabb_create_empty();
}

void	mesh_free(t_mesh_asset *mesh)
{
    if (!mesh)
        return ;
    if (mesh->vertices)
        free(mesh->vertices);
    if (mesh->normals)
        free(mesh->normals);
    if (mesh->uvs)
        free(mesh->uvs);
    if (mesh->indices)
        free(mesh->indices);
    if (mesh->bone_ids)
        free(mesh->bone_ids);
    if (mesh->weights)
        free(mesh->weights);
    if (mesh->weight_counts)
        free(mesh->weight_counts);
    if (mesh->weight_offsets)
        free(mesh->weight_offsets);
    if (mesh->skeleton)
        free(mesh->skeleton);
    if (mesh->bone_matrices)
        free(mesh->bone_matrices);
    if (mesh->name)
        free(mesh->name);
    ft_memset(mesh, 0, sizeof(t_mesh_asset));
}
