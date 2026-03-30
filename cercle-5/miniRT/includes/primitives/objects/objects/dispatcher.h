/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:19:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_DISPATCHER_H
# define PRIMITIVES_DISPATCHER_H

# include "parser.h"
# include "rt.h"
# include "mesh.h"

typedef struct s_scene	t_scene;

struct					s_mesh_info
{
	char				*path;
	t_transform			transform;
	t_vec3				color;
	t_vec3				emission;
};

typedef struct s_parse_obj
{
	t_type				type;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		t_cone			cone;
		t_tri_shape		tri_shape;
		t_rect			rect;
		t_pyramid		pyramid;
		t_box			box;
		t_capsule		capsule;
		t_light			light;
		t_camera		camera;
		t_ambient		ambient;
		struct s_mesh_info	mesh_info;
	}					data;
}						t_parse_obj;

typedef struct s_rt
{
	t_parser			*parser;
	int					fd;
	char				id[16];
	t_parse_obj			*obj;
	bool				status;
}						t_rt;

/* Dispatcher Prototypes (srcs/objects/dispatcher/) */
t_parse_obj				dispatch_scan(t_parser *p, char *id);

/* RT Parser Logic Prototypes (srcs/objects/rt/parser/) */
bool					rt_init_parser(t_rt *rt, const char *path);
bool					rt_parse_loop(t_scene *scene, t_rt *rt);
bool					rt_parse_entry(t_scene *scene, t_rt *rt);

#endif
