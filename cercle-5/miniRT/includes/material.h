/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

/* 1. EXTERNAL DEPENDENCIES */
# include "maths.h"

/* 2. FORWARD DECLARATIONS & TYPES */
# include "types.h"

/* 3. MODULE TYPES */
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
	t_texture albedo_map; // Replaces t_vec3 albedo
	t_texture bump_map;   // Optional bump texture

	double		specular;
	double		shininess;
	double		metallic;
	double		roughness;
	t_vec3		emission;
	double		refract_index;
	double		transparency;
	double		reflectivity;
}				t_material;

/* 4. FUNCTION PROTOTYPES */
t_material		*create_material(t_vec3 albedo, double metallic,
					double roughness, t_vec3 emission, double refract_index,
					double transparency, double reflectivity);

// Texture functions
t_vec3			sample_texture(t_texture *tex, double u, double v);

#endif
