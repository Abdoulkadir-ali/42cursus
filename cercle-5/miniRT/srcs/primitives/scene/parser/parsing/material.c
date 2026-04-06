/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:08:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static t_parse_obj	parse_mat_solid(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_SOLID;
	res.data.mat_mod.scale = 1.0;
	parse_vec3(p, &res.data.mat_mod.color_a);
	res.type = TYPE_MAT_MOD;
	return (res);
}

static t_parse_obj	parse_mat_checker(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_CHECKER;
	res.data.mat_mod.scale = 1.0;
	parse_vec3(p, &res.data.mat_mod.color_a);
	parse_vec3(p, &res.data.mat_mod.color_b);
	parser_skip_horizontal_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n' && parser_peek(p) != '\r'
		&& parser_peek(p) != '#')
		res.data.mat_mod.scale = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}

static t_parse_obj	parse_mat_texture(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_TEXTURE;
	parse_path_safe(p, res.data.mat_mod.path, sizeof(res.data.mat_mod.path));
	res.type = TYPE_MAT_MOD;
	return (res);
}

/**
 * Parses: mat s <r,g,b>
 *         mat c <r1,g1,b1> <r2,g2,b2> [scale]
 *         mat t <path>
 */
t_parse_obj	parse_mat_mod(t_parser *p)
{
	char	mode;

	parser_skip_horizontal_spaces(p);
	mode = parser_peek(p);
	parser_advance(p);
	if (mode == 's')
		return (parse_mat_solid(p));
	if (mode == 'c')
		return (parse_mat_checker(p));
	if (mode == 't')
		return (parse_mat_texture(p));
	return ((t_parse_obj){.type = TYPE_NONE});
}

/**
 * Parses: rough <val>  metal <val>  emit <r,g,b>
 *         opac <val>   refl <val>   ior <val>  shine <val>
 *         uv_scale <val>  emit_power <val>
 */
t_parse_obj	parse_prop_mod(t_parser *p, t_mat_mod_kind kind)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = kind;
	if (kind == MAT_MOD_EMISSION)
		parse_vec3(p, &res.data.mat_mod.color_a);
	else
		res.data.mat_mod.val = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}

/**
 * Parses: bump <path>
 */
t_parse_obj	parse_bump_mod(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_BUMP;
	parse_path_safe(p, res.data.mat_mod.path, sizeof(res.data.mat_mod.path));
	res.type = TYPE_MAT_MOD;
	return (res);
}

/**
 * Parses: name <string>
 */
t_parse_obj	parse_name_mod(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_NAME;
	parse_path_safe(p, res.data.mat_mod.path, sizeof(res.data.mat_mod.path));
	res.type = TYPE_MAT_MOD;
	return (res);
}

/**
 * Parses: phys mass <f>  /  phys static <0|1>
 *         phys elast <f>  /  phys fric <f>
 */
t_parse_obj	parse_phys_mod(t_parser *p)
{
	t_parse_obj	res;
	char		sub[16];

	ft_memset(&res, 0, sizeof(res));
	parser_skip_horizontal_spaces(p);
	if (!read_id(p, sub, sizeof(sub)))
		return ((t_parse_obj){.type = TYPE_NONE});
	if (ft_strcmp(sub, "mass") == 0)
		res.data.mat_mod.kind = MAT_MOD_PHYS_MASS;
	else if (ft_strcmp(sub, "static") == 0)
		res.data.mat_mod.kind = MAT_MOD_PHYS_STATIC;
	else if (ft_strcmp(sub, "elast") == 0)
		res.data.mat_mod.kind = MAT_MOD_PHYS_ELAST;
	else if (ft_strcmp(sub, "fric") == 0)
		res.data.mat_mod.kind = MAT_MOD_PHYS_FRIC;
	else
		return ((t_parse_obj){.type = TYPE_NONE});
	res.data.mat_mod.val = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}
