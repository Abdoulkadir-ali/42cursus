/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:23:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:23:40 by abdoali          ###   ########.fr       */
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
