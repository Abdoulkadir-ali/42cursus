/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:46:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "functions/primitives/parser.h"
# include "helpers.h"
# include "types.h"
# include "surface.h"

/* Resource Factory (srcs/objects/meshes/resource.c) */
bool					mesh_resource_add_mesh(t_mesh_resource *res,
							t_mesh mesh);
int						mesh_resource_add_material(t_mesh_resource *res,
							const char *name);
void					mesh_resource_init(t_mesh_resource *res);
void					mesh_resource_free(t_mesh_resource *res);
void					mesh_build_bvh(t_mesh *mesh);
void					mesh_free(t_mesh *mesh);

#endif
