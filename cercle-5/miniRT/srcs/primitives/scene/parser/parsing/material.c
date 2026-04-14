/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 11:17:27 by abdoali          ###   ########.fr       */
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

static t_mat_mod_kind	match_phys_mod(const char *sub)
{
	if (ft_strcmp(sub, "mass") == 0)
		return (MAT_MOD_PHYS_MASS);
	if (ft_strcmp(sub, "static") == 0)
		return (MAT_MOD_PHYS_STATIC);
	if (ft_strcmp(sub, "elast") == 0)
		return (MAT_MOD_PHYS_ELAST);
	if (ft_strcmp(sub, "fric") == 0)
		return (MAT_MOD_PHYS_FRIC);
	if (ft_strcmp(sub, "vel") == 0)
		return (MAT_MOD_PHYS_VEL);
	if (ft_strcmp(sub, "charge") == 0)
		return (MAT_MOD_PHYS_MAGNETIC);
	return ((t_mat_mod_kind)-1);
}

t_parse_obj	parse_phys_mod(t_parser *p)
{
	t_parse_obj	res;
	char		sub[16];

	ft_memset(&res, 0, sizeof(res));
	parser_skip_horizontal_spaces(p);
	if (!read_id(p, sub, sizeof(sub)))
		return ((t_parse_obj){.type = TYPE_NONE});
	res.data.mat_mod.kind = match_phys_mod(sub);
	if (res.data.mat_mod.kind == (t_mat_mod_kind)-1)
		return ((t_parse_obj){.type = TYPE_NONE});
	if (res.data.mat_mod.kind == MAT_MOD_PHYS_VEL)
	{
		parse_vec3(p, &res.data.mat_mod.color_a);
		res.type = TYPE_MAT_MOD;
		return (res);
	}
	res.data.mat_mod.val = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}
