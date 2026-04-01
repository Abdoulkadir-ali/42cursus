/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_surface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:27:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:40:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_SURFACE_H
# define TYPES_PRIMITIVES_SURFACE_H

# include "t_maths.h"

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

#endif
