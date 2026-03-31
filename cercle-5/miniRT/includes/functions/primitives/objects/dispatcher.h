/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_DISPATCHER_H
# define OBJECTS_DISPATCHER_H

# include "helpers.h"
# include "types.h"

/* RT Parser Dispatch (srcs/primitives/objects/rt_scene/dispatch.c) */
t_parse_obj				dispatch_scan(t_parser *p, char *id);

/* Shape Parsers (srcs/primitives/objects/rt_scene/shapes/) */
t_parse_obj				parse_ambient(t_parser *p);
t_parse_obj				parse_camera(t_parser *p);
t_parse_obj				parse_light(t_parser *p);
t_parse_obj				parse_sphere(t_parser *p);
t_parse_obj				parse_plane(t_parser *p);
t_parse_obj				parse_cylinder(t_parser *p);
t_parse_obj				parse_cone(t_parser *p);
t_parse_obj				parse_tri_shape(t_parser *p);
t_parse_obj				parse_rect(t_parser *p);
t_parse_obj				parse_pyramid(t_parser *p);
t_parse_obj				parse_box(t_parser *p);
t_parse_obj				parse_capsule(t_parser *p);
t_parse_obj				parse_spot_light(t_parser *p);

/* Mesh Entry Parsers (srcs/primitives/objects/rt_scene/meshes/) */
t_parse_obj				parse_mesh_entry(t_parser *p, t_type type);

/* Extension Helpers (srcs/primitives/objects/rt/extension.c) */
const char				*rt_get_extension(const char *path);

#endif
