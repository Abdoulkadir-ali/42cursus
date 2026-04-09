/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 19:32:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_parse_obj	parse_scene_gravity(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_SCENE_GRAVITY;
	if (!parse_vec3(p, &res.data.mat_mod.color_a))
		return (res);
	res.type = TYPE_MAT_MOD;
	return (res);
}

t_parse_obj	parse_big_g(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_SCENE_BIG_G;
	res.data.mat_mod.val = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}

t_parse_obj	parse_scene_damp(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.data.mat_mod.kind = MAT_MOD_SCENE_DAMP;
	res.data.mat_mod.val = parse_double(p);
	res.type = TYPE_MAT_MOD;
	return (res);
}
