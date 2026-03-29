/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:16:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_LOADER_H
# define MATERIAL_LOADER_H

# include "parser.h"
# include "utils.h"
# include "scene.h"
# include "surface.h"

/* --- INJECTION --- */
int			scene_add_material(t_scene *scene, const t_material *mat);
int		    scene_add_material_from_color(t_scene *scene, t_vec3 color);
int		    scene_add_named_material(t_scene *scene, const char *name);
void		init_metadata_material(t_material_metadata *meta,
				const t_material *mat);

/* --- HELPERS --- */
int			scene_find_material(t_scene *sc, const char *name);

#endif
