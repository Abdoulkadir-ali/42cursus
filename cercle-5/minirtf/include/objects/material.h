/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:59:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "maths.h"

# define MAT_NAME_LEN 32

typedef enum e_tex_kind
{
	TEX_NONE = 0,
	TEX_CHECKER = 1,
	TEX_IMAGE = 2
}				t_tex_kind;

typedef struct s_mipmap
{
	int				w;
	int				h;
	unsigned char	*pixels;
}					t_mipmap;

typedef struct s_texture
{
	int				kind;
	int				w;
	int				h;
	unsigned char	*pixels;
	t_mipmap		mips[12];
	int				n_mips;
	t_vec3			color_a;
	t_vec3			color_b;
	float			scale;
}					t_texture;

typedef struct s_material
{
	t_vec3	albedo;
	float	ks;
	float	shininess;
	float	reflectivity;
	int		tex_id;
	int		emit_tex_id;
	float	temperature;
	float	emission;
	float	roughness;
	float	metallic;
	float	opacity;
	float	ior;
	t_vec3	emit_color;
	float	emit_power;
	char	name[MAT_NAME_LEN];
}			t_material;

struct s_app;
struct s_scene;
struct s_hit;
struct s_light;

t_vec3	material_albedo(const struct s_app *app, const t_material *m,
			float u, float v, float dist);
t_vec3	emissive_color(const t_material *m);
void	mat_init_default(t_material *m, t_vec3 albedo);
t_vec3	texture_sample(const t_texture *t, float u, float v, float lod);
void	texture_generate_mips(t_texture *t);
int		texture_make_checker(struct s_scene *s, t_vec3 a, t_vec3 b, float scale);
int		texture_push_image(struct s_scene *s, unsigned char *pixels, int w,
			int h);

#endif
