/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:34:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 17:34:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_H
# define SURFACE_H

/* 1. EXTERNAL DEPENDENCIES */
# include "core.h"
# include "debug.h"
# include "maths.h"
typedef struct s_scene	t_scene;



/* 2. MODULE TYPES */
typedef enum e_tex_type
{
	TEX_SOLID,
	TEX_CHECKER,
	TEX_BITMAP,
	TEX_BUMP
}				t_tex_type;

typedef struct s_texture
{
	t_tex_type	type;
	t_vec3		color_a;
	t_vec3		color_b;
	double		scale;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			len;
	int			endian;
}				t_texture;

typedef struct s_material
{
	char		*name; /* Added for MTL parsing. */
	t_texture	albedo_map; /* Replaces t_vec3 albedo. */
	t_texture	bump_map; /* Optional bump texture. */
	double		specular;
	double		shininess;
	double		metallic;
	double		roughness;
	t_vec3		emission;
	double		refract_index;
	double		transparency;
	double		reflectivity;
}				t_material;

typedef struct s_material_params
{
	t_vec3		albedo;
	double		metallic;
	double		roughness;
	t_vec3		emission;
	double		refract_index;
	double		transparency;
	double		reflectivity;
}					t_material_params;

/* 3. FUNCTION PROTOTYPES */
t_material		*create_material(t_material_params params);

int					scene_add_material(t_scene *scene, t_vec3 color);
int					scene_find_material(t_scene *scene, const char *name);
int					scene_add_named_material(t_scene *scene, const char *name);
int					scene_add_checker_material(t_scene *scene, t_vec3 color_a,
					t_vec3 color_b, double scale);

void	convert_rgba_to_bgra(unsigned char *data, int size);
void	init_texture_props(t_texture *tex, int w, int h, char *data);
bool	load_texture_xpm(t_scene *scene, t_texture *tex, const char *path);
bool	load_texture(t_scene *scene, t_texture *tex, const char *path);
t_vec3	sample_texture(t_texture *tex, double u, double v);

#endif
