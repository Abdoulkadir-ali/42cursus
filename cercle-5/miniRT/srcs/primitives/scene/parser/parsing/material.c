/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:23:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

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

t_parse_obj	parse_bump_mod(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_BUMP;
	parse_path_safe(p, res.data.mat_mod.path, sizeof(res.data.mat_mod.path));
	res.type = TYPE_MAT_MOD;
	return (res);
}

t_parse_obj	parse_name_mod(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_NAME;
	parse_path_safe(p, res.data.mat_mod.path, sizeof(res.data.mat_mod.path));
	res.type = TYPE_MAT_MOD;
	return (res);
}

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
