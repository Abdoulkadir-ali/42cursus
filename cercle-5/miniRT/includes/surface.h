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

# define BITS_PER_BYTE 8
# define COLOR_MAGENTA (t_vec3){255.0, 0.0, 255.0}
# define COLOR_CYAN (t_vec3){0.0, 255.0, 255.0}
# define COLOR_BLUE (t_vec3){0.0, 0.0, 255.0}
# define COLOR_LAVENDER (t_vec3){200.0, 160.0, 255.0}
# define COLOR_YELLOW (t_vec3){255.0, 255.0, 0.0}

# define TEX_DEFAULT_SCALE 1.0
# define TEX_DEFAULT_BPP 32
# define TEX_CH_RGBA 4
# define TEX_CENTER_OFFSET 0.5
# define COLOR_WHITE (t_vec3){255.0, 255.0, 255.0}
# define COLOR_BLACK (t_vec3){0.0, 0.0, 0.0}

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
	t_texture	roughness_map; /* Added for PBR. */
	t_texture	metallic_map; /* Added for PBR. */
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

typedef struct s_bilinear
{
	double	ux;
	double	uy;
	int		xi;
	int		yi;
	double	wx;
	double	wy;
}				t_bilinear;

/* 3. FUNCTION PROTOTYPES */
t_material		*create_material(t_material_params params);

int					scene_add_material(t_scene *scene, t_vec3 color);
int					scene_add_fresh_material(t_scene *scene, t_vec3 color);
int					scene_clone_material(t_scene *scene, int src_id);
int					scene_find_material(t_scene *scene, const char *name);
int					scene_add_named_material(t_scene *scene, const char *name);
int					scene_add_checker_material(t_scene *scene, t_vec3 color_a,
					t_vec3 color_b, double scale);

void	convert_rgba_to_bgra(unsigned char *data, int size);
void	init_texture_props(t_texture *tex, int w, int h, char *data);
bool	load_texture(t_scene *scene, t_texture *tex, const char *path);
bool	load_texture_from_memory(t_texture *tex, unsigned char *buffer, int size);
t_vec3	sample_texture(t_texture *tex, double u, double v);
t_vec3	sample_checker(t_texture *tex, double u, double v);
t_vec3	sample_bitmap(t_texture *tex, double u, double v);
t_vec3	texel_at(t_texture *tex, int x, int y);

void	material_apply_preset(t_material *m, t_vec3 color);
bool	load_stbi(t_texture *tex, const char *path);

#endif
