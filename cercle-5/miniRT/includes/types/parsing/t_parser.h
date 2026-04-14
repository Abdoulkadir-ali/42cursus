/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 11:23:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PARSING_PARSER_H
# define TYPES_PARSING_PARSER_H

# define PARSER_BUF_SIZE 65536
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

/* JSON Parser Types */
typedef enum e_json_type
{
	JSON_NULL,
	JSON_BOOL,
	JSON_NUMBER,
	JSON_STRING,
	JSON_ARRAY,
	JSON_OBJECT
}						t_json_type;

typedef struct s_parser
{
	int					fd;
	char				buffer[PARSER_BUF_SIZE + 1];
	size_t				cursor;
	size_t				bytes_read;
	bool				eof;
}						t_parser;

typedef enum e_mat_mod_kind
{
	MAT_MOD_SOLID,
	MAT_MOD_CHECKER,
	MAT_MOD_TEXTURE,
	MAT_MOD_ROUGHNESS,
	MAT_MOD_METALLIC,
	MAT_MOD_EMISSION,
	MAT_MOD_OPACITY,
	MAT_MOD_REFLECTIVITY,
	MAT_MOD_IOR,
	MAT_MOD_SHININESS,
	MAT_MOD_UV_SCALE,
	MAT_MOD_EMIT_POWER,
	MAT_MOD_BUMP,
	MAT_MOD_NAME,
	MAT_MOD_PHYS_MASS,
	MAT_MOD_PHYS_STATIC,
	MAT_MOD_PHYS_ELAST,
	MAT_MOD_PHYS_FRIC,
	MAT_MOD_PHYS_VEL,
	MAT_MOD_PHYS_MAGNETIC,
	MAT_MOD_SCENE_GRAVITY,
	MAT_MOD_SCENE_BIG_G,
	MAT_MOD_SCENE_DAMP,
	MAT_MOD_SCENE_WIND,
	MAT_MOD_SCENE_TURBULENCE,
	MAT_MOD_TEMPERATURE
}							t_mat_mod_kind;

typedef struct s_mat_mod
{
	t_mat_mod_kind			kind;
	t_vec3					color_a;
	t_vec3					color_b;
	double					val;
	double					scale;
	char					path[512];
}							t_mat_mod;

typedef struct s_parse_obj
{
	t_type					type;
	union
	{
		t_sphere			sphere;
		t_plane				plane;
		t_cylinder			cylinder;
		t_cone				cone;
		t_tri_shape			tri_shape;
		t_rect				rect;
		t_pyramid			pyramid;
		t_box				box;
		t_capsule			capsule;
		t_attractor			attractor;
		t_light				light;
		t_camera			camera;
		t_ambient			ambient;
		t_mesh_info			mesh_info;
		t_mat_mod			mat_mod;
		t_emitter					emitter;
	}					data;
}						t_parse_obj;

typedef struct s_rt
{
	t_parser				*parser;
	int						fd;
	char					id[16];
	t_parse_obj				obj;
	bool					status;
	t_type					last_type;
	bool					last_mat_cloned;
	int						line_num;
}							t_rt;

#endif
