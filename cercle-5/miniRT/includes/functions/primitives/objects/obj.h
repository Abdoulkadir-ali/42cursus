/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:48:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "mesh.h"


/* Prototypes (srcs/objects/meshes/obj/) */
bool					parse_obj_worker(const char *path, struct s_scene *scene);
bool					obj_build_mesh(struct s_scene *scene, t_obj *obj,
							const char *path);
bool					obj_parse_mtllib(t_scene *scene, t_obj *obj,
							t_parser *p, const char *path);
bool					obj_parse_usemtl(t_scene *scene, t_obj *obj,
							t_parser *p);
bool					parse_mtl(t_scene *scene, t_obj *obj, const char *path);
bool					scene_parse_obj_worker(const char *path, t_scene *scene);
void					obj_parse_v(t_obj *obj, t_parser *p);
void					obj_parse_vt(t_obj *obj, t_parser *p);
void					obj_parse_vn(t_obj *obj, t_parser *p);
void					obj_parse_f(t_obj *obj, t_parser *p);
bool					obj_read_id(t_parser *p, char *buf, size_t size);
void					obj_skip_line(t_parser *p);

void					obj_add_vert(t_obj *obj, int vi, int vti, int vni);
void					obj_set_out_vertex(t_obj *obj, size_t vi,
							size_t vti, size_t vni);
void					obj_generate_normals(t_obj *obj);
void					obj_init_mesh(t_mesh *mesh, t_obj *obj, const char *path);
void					obj_face_init(t_obj_face *face);
void					obj_face_read(t_parser *p, t_obj_face *face);
void					obj_face_read_slash(t_parser *p, t_obj_face *face);
void					obj_face_emit_tris(t_obj *obj, t_obj_face *face);

#endif
