/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:38:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include "parser.h"
# include "scene.h"
# include "material.h"

/* --- OBJ LOADER STRUCTURE --- */
typedef struct s_obj
{
	/* Temp parsing storage */
	t_vec3	*temp_v;
	t_vec2	*temp_vt;
	t_vec3	*temp_vn;
	size_t	v_count;
	size_t	v_cap;
	size_t	vt_count;
	size_t	vt_cap;
	size_t	vn_count;
	size_t	vn_cap;

	/* Final output mesh storage */
	t_vec3	*out_v;
	t_vec2	*out_vt;
	t_vec3	*out_vn;
	int		*out_i;
	size_t	out_v_count;
	size_t	out_v_cap;
	size_t	out_i_count;
	size_t	out_i_cap;

	/* State Management */
	int		current_mat_id;
	int		first_mtl_id;
	t_aabb	bbox;
}			t_obj;
/* --- OBJ FACE STRUCTURE --- */
typedef struct s_obj_face
{
	int		vi[32];
	int		vti[32];
	int		vni[32];
	int		count;
}			t_obj_face;

/* --- PUBLIC API --- */
bool		obj_load(t_scene *scene, const char *path);
bool		obj_parse_to_asset(t_obj *obj, const char *path);
bool		parse_obj_entry(t_scene *scene, t_parser *p);

/* --- MATERIAL INJECTION --- */
/* Materials are created via scene_add_material() from material/inject.c.
 * MTL files (.mtl) reference materials by name or RGB values parsed during load.
 */

/* --- PARSING --- */
void		obj_parse_v(t_obj *obj, t_parser *p);
void		obj_parse_vt(t_obj *obj, t_parser *p);
void		obj_parse_vn(t_obj *obj, t_parser *p);
void		obj_parse_f(t_obj *obj, t_parser *p);
void		obj_face_init(t_obj_face *face);
void		obj_face_read(t_parser *p, t_obj_face *face);
void		obj_face_read_slash(t_parser *p, t_obj_face *face);
void		obj_face_emit_tris(t_obj *obj, t_obj_face *face);

/* --- MTL INTEGRATION --- */
void		obj_parse_mtllib_to_scene(t_obj *obj, t_parser *p, t_scene *scene,
				const char *obj_path);
void		obj_parse_usemtl_to_scene(t_obj *obj, t_parser *p, t_scene *scene);

/* --- FINALIZE & HELPERS --- */
void		obj_generate_normals(t_obj *obj);
void		obj_init_mesh(t_mesh *mesh, t_obj *obj, const char *path);
void		obj_free_obj(t_obj *obj);
void		obj_set_mat_id(t_mesh *mesh, t_obj *obj);
void		obj_skip_line(t_parser *p);
bool		obj_read_id(t_parser *p, char *buf, size_t max_len);
void		obj_add_vert(t_obj *obj, int vi, int vti, int vni);

/* --- MTL PARSING UTILITIES (OBJ-specific) --- */
char		*mtl_resolve_path(const char *mtl_path, const char *tex_filename);
void		mtl_trim_line_end(char *p);
char		*mtl_skip_ws(char *p);
bool		mtl_is_tag(char *p, const char *tag);
bool		mtl_open(const char *path, int *fd);
bool		mtl_load_to_scene(const char *path, t_scene *scene);

/* --- RAW PARSING (For non-scene loading) --- */
typedef struct s_raw_model t_raw_model; /* Forward */
void		mtl_parse_lines_raw(t_raw_model *model, t_parser *parser,
				int *cur_mat_idx, const char *obj_path);

/* --- INJECTION (Scene add functions) --- */
bool		scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
