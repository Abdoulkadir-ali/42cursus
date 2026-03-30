/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:34:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:26:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_H
# define SURFACE_H

# include "helpers.h"
# include "mlx.h"
#include "../../packages/stb_image.h"


typedef enum e_tex_type
{
	TEX_SOLID,
	TEX_CHECKER,
	TEX_BITMAP,
	TEX_BUMP
}						t_tex_type;

typedef struct s_texture
{
	t_tex_type			type;
	t_vec3				color_a;
	t_vec3				color_b;
	double				scale;
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					len;
	int					endian;
}						t_texture;

typedef struct s_material
{
	char				*name;
	t_texture			albedo_map;
	t_texture			bump_map;
	t_texture			roughness_map;
	t_texture			metallic_map;
	double				specular;
	double				shininess;
	double				metallic;
	double				roughness;
	t_vec3				emission;
	double				refract_index;
	double				transparency;
	double				reflectivity;
}						t_material;

/* Function Prototypes (srcs/objects/surface/) */
t_material				*create_material(t_material material);
void					convert_rgba_to_bgra(unsigned char *data, int size);
void					init_texture_props(t_texture *tex, int w, int h,
							char *data);
bool					load_texture_from_memory(t_texture *tex,
							unsigned char *buffer, int size);
bool					load_texture(void *mlx_ptr, t_texture *tex,
							const char *path);
bool					load_xpm(void *mlx_ptr, t_texture *tex,
							const char *path);
bool					load_stbi(t_texture *tex, const char *path);
t_vec3					sample_texture(t_texture *tex, double u, double v);

#endif
