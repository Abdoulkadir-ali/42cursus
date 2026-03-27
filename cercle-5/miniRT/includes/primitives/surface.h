/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:34:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:02:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_H
#define SURFACE_H

/* 1. EXTERNAL DEPENDENCIES */
# include "helpers.h"


/* Color constants moved into a runtime-initialized struct to satisfy
 * style rules (no non-constant preprocessor values). Use `g_colors.*`.
 */
typedef struct s_colors
{
	t_vec3		pink;
	t_vec3		magenta;
	t_vec3		cyan;
	t_vec3		blue;
	t_vec3		lavender;
	t_vec3		yellow;
	t_vec3		white;
	t_vec3		black;
	t_vec3		green;
}				t_colors;

const t_colors	*get_colors(void);


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
	char		*name;
	t_texture	albedo_map;
	t_texture	bump_map;
	t_texture	roughness_map;
	t_texture	metallic_map;
	double		specular;
	double		shininess;
	double		metallic;
	double		roughness;
	t_vec3		emission;
	double		refract_index;
	double		transparency;
	double		reflectivity;
}				t_material;

typedef struct s_material_args
{
	t_vec3		albedo;
	double		metallic;
	double		roughness;
	t_vec3		emission;
	double		refract_index;
	double		transparency;
	double		reflectivity;
}				t_material_args;

typedef struct			s_bilinear
{
	double		ux;
	double		uy;
	int			xi;
	int			yi;
	double		wx;
	double		wy;
 } t_bilinear;

/* 3. FUNCTION PROTOTYPES */
t_material		*create_material(t_material_args params);

int				scene_add_material(t_scene *scene, t_vec3 color);
int				scene_add_fresh_material(t_scene *scene, t_vec3 color);
int				scene_clone_material(t_scene *scene, int src_id);
int				scene_find_material(t_scene *scene, const char *name);
int				scene_add_named_material(t_scene *scene, const char *name);
int				scene_add_checker_material(t_scene *scene, t_vec3 color_a,
					t_vec3 color_b, double scale);

void			convert_rgba_to_bgra(unsigned char *data, int size);
void			init_texture_props(t_texture *tex, int w, int h, char *data);
bool			load_texture(t_scene *scene, t_texture *tex, const char *path);
bool				load_texture_with_mlx(void *mlx, t_texture *tex, const char *path);
bool			load_texture_from_memory(t_texture *tex, unsigned char *buffer,
					int size);
t_vec3			sample_texture(t_texture *tex, double u, double v);
t_vec3			sample_checker(t_texture *tex, double u, double v);
t_vec3			sample_bitmap(t_texture *tex, double u, double v);
t_vec3			texel_at(t_texture *tex, int x, int y);

void			material_apply_preset(t_material *m, t_vec3 color);
bool			load_stbi(t_texture *tex, const char *path);

#endif
