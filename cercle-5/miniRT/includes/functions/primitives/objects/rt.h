/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:46:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "fbx.h"
# include "obj.h"
# include "glb.h"
# include "fdf.h"


/* Dispatcher Prototypes (srcs/objects/dispatcher/) */
t_parse_obj				dispatch_scan(t_parser *p, char *id);

/* RT Parser Logic Prototypes (srcs/objects/rt/parser/) */
bool					rt_init_parser(t_rt *rt, const char *path);
bool					rt_parse_loop(t_scene *scene, t_rt *rt);
bool					rt_parse_entry(t_scene *scene, t_rt *rt);


/* RT Shape Parsers */
t_parse_obj				parse_ambient(t_parser *p);
t_parse_obj				parse_camera(t_parser *p);
t_parse_obj				parse_light(t_parser *p);
t_parse_obj				parse_spot_light(t_parser *p);
t_parse_obj				parse_sphere(t_parser *p);
t_parse_obj				parse_plane(t_parser *p);
t_parse_obj				parse_cylinder(t_parser *p);
t_parse_obj				parse_cone(t_parser *p);
t_parse_obj				parse_tri_shape(t_parser *p);
t_parse_obj				parse_rect(t_parser *p);
t_parse_obj				parse_pyramid(t_parser *p);
t_parse_obj				parse_box(t_parser *p);
t_parse_obj				parse_capsule(t_parser *p);
t_parse_obj				parse_mesh_entry(t_parser *p, t_type type);

#endif
