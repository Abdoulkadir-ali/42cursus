/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:08:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_DISPATCHER_H
# define OBJECTS_DISPATCHER_H

# include "helpers.h"
# include "types.h"

/* Shared Parsing Helpers (srcs/primitives/scene/parser/parsing/shared.c) */
void						init_poly_phys(t_physics_body *phys);
bool						parse_cylinder_base(t_parser *p, t_cylinder *out);

/* RT Parser Dispatch (srcs/primitives/objects/rt_scene/dispatch.c) */
t_parse_obj				dispatch_scan(t_parser *p, char *id);
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
t_parse_obj				parse_mesh_entry(t_parser *p, t_type type);
t_parse_obj				parse_mat_mod(t_parser *p);
t_parse_obj				parse_prop_mod(t_parser *p, t_mat_mod_kind kind);
t_parse_obj				parse_bump_mod(t_parser *p);
t_parse_obj				parse_name_mod(t_parser *p);
t_parse_obj				parse_phys_mod(t_parser *p);
const char				*rt_get_extension(const char *path);

/* Dispatch (srcs/primitives/scene/add/objects/mesh/dispatch/) */
bool					process_primitive(t_scene *scene, t_parse_obj obj);
bool					process_system(t_scene *scene, t_parse_obj obj);
bool					process_object(t_scene *scene, t_parse_obj obj);

/* RT Parser (srcs/primitives/scene/parser/) */
bool					rt_parse_loop(t_scene *scene, t_rt *rt);
bool					rt_parse_entry(t_scene *scene, t_rt *rt);
bool					validate_file(const char *path);
bool					parse_rt_worker(const char *path, t_scene *scene);
void					apply_mat_mod_to_last(t_scene *scene, t_rt *rt, t_mat_mod *mod);

#endif
