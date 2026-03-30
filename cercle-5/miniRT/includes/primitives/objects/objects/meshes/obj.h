/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:30:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "mesh.h"
# include "../../parser/parser.h"

typedef struct s_obj			t_obj;
typedef struct s_scene			t_scene;

typedef struct s_obj_face
{
	int					vi[32];
	int					vti[32];
	int					vni[32];
	int					count;
}						t_obj_face;

typedef struct s_obj
{
	t_vec3				*temp_v;
	size_t				v_count;
	size_t				v_cap;
	t_vec2				*temp_vt;
	size_t				vt_count;
	size_t				vt_cap;
	t_vec3				*temp_vn;
	size_t				vn_count;
	size_t				vn_cap;

	t_vertex			*out_v;
	int					out_v_count;
	int					out_v_cap;
	int					*out_i;
	int					out_i_count;
	int					out_i_cap;

	t_aabb				bbox;
	int					current_mat_id;
	int					first_mtl_id;
}						t_obj;

/* Prototypes (srcs/objects/meshes/obj/) */
bool					parse_obj(const char *path, t_mesh_resource *out,
							void *mlx_ptr);
bool					obj_build_mesh(t_mesh_resource *out, t_obj *obj,
							const char *path, void *mlx_ptr);
void					obj_parse_v(t_obj *obj, t_parser *p);
void					obj_parse_vt(t_obj *obj, t_parser *p);
void					obj_parse_vn(t_obj *obj, t_parser *p);
void					obj_parse_f(t_obj *obj, t_parser *p);
void					obj_parse_mtllib(t_obj *obj, t_parser *p,
							t_scene *scene, const char *path);
void					obj_parse_usemtl(t_obj *obj, t_parser *p,
							t_scene *scene);
bool					obj_read_id(t_parser *p, char *buf, size_t size);
void					obj_skip_line(t_parser *p);

void					obj_face_init(t_obj_face *face);
void					obj_face_read(t_parser *p, t_obj_face *face);
void					obj_face_read_slash(t_parser *p, t_obj_face *face);
void					obj_face_emit_tris(t_obj *obj, t_obj_face *face);

#endif
