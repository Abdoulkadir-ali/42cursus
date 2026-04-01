/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:45:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "utils.h"

void	mesh_resource_init(t_mesh_resource *res)
{
	ft_memset(res, 0, sizeof(t_mesh_resource));
}

bool	mesh_resource_add_mesh(t_mesh_resource *res, t_mesh mesh)
{
	if (!DYNARRAY_ENSURE_INT(&res->meshes, &res->mesh_count, &res->mesh_cap,
			sizeof(t_mesh)))
		return (false);
	res->meshes[res->mesh_count++] = mesh;
	return (true);
}

int	mesh_resource_add_material(t_mesh_resource *res, const char *name)
{
	t_material	*m;

	if (!DYNARRAY_ENSURE_INT(&res->materials, &res->mat_count, &res->mat_cap,
			sizeof(t_material)))
		return (-1);
	m = &res->materials[res->mat_count];
	ft_memset(m, 0, sizeof(t_material));
	m->name = ft_strdup(name);
	m->albedo_map.type = TEX_SOLID;
	m->albedo_map.color_a = vec3(255, 255, 255);
	m->albedo_map.scale = 1.0;
	m->specular = 0.1;
	m->shininess = 16.0;
	return (res->mat_count++);
}

void	mesh_resource_free(t_mesh_resource *res)
{
	int	i;

	i = 0;
	while (i < res->mat_count)
		free(res->materials[i++].name);
	free(res->materials);
	i = 0;
	while (i < res->mesh_count)
	{
		free(res->meshes[i].vertices);
		free(res->meshes[i].triangles);
		free(res->meshes[i].name);
		i++;
	}
	free(res->meshes);
	i = 0;
	while (i < res->group_count)
		free(res->groups[i++].name);
	free(res->groups);
}
