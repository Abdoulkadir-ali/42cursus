/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 06:57:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_LOADER_H
# define GLB_LOADER_H

# include "parser.h"
# include "scene.h"
# include "material.h"

/* --- GLB LOADER STRUCTURE --- */
typedef struct s_glb
{
	t_mesh			*meshes;
	int				*mesh_mats;
	int				mesh_count;
	t_animation		*animations;
	int				anim_count;
	t_material		*materials;
	int				mat_count;
	const char		*path;
	t_json_value	*json;
	char			*bin_ref;
}					t_glb;

/* --- PUBLIC API --- */
bool				glb_load(t_scene *scene, const char *path);
bool				parse_glb_entry(t_scene *scene, t_parser *p);

/* --- MATERIAL PARSING & INJECTION --- */
/* GLB loader parses embedded materials as t_material structs.
 * Materials are injected via scene_add_material() from material/injection.c
 */

/* --- INTERNALS --- */
bool				glb_parse_to_asset(t_glb *g, int fd, const char *path);
void				glb_clear_asset(t_glb *g);

/* --- INJECTION (Scene add functions) --- */
bool				scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
