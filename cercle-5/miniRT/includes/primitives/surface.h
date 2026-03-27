/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:34:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 17:37:49 by abdoali          ###   ########.fr       */
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
	t_tex_type		type;
	t_vec3			color_a;
	t_vec3			color_b;
	double			scale;
	int				width;
	int				height;
	int				bpp;
	int				len;
	int				endian;
	unsigned char	*addr;
	void			*img;        /* Legacy MLX ref if needed */
	int				pool_idx;    /* DOD: Texture pool mapping */
	char			*path;       /* Track resource identity */
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
/* Material management is part of the scene module. Prototypes were moved
 * to the scene headers to avoid coupling `surface.h` to scene internals.
 */

 
t_material		*create_material(void);
void			convert_rgba_to_bgra(unsigned char *data, int size);
void			init_texture_props(t_texture *tex, int w, int h, unsigned char *data);
bool			load_texture(t_scene *scene, t_texture *tex, const char *path);
bool			load_texture_from_memory(t_texture *tex, unsigned char *buffer,
					int size);
t_vec3			sample_texture(t_texture *tex, double u, double v);
t_vec3			sample_checker(t_texture *tex, double u, double v);
t_vec3			sample_bitmap(t_texture *tex, double u, double v);
t_vec3			texel_at(t_texture *tex, int x, int y);

void			material_apply_preset(t_material *m, t_vec3 color);
bool			load_stbi(t_texture *tex, const char *path);

#endif
