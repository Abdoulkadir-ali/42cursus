/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:25:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_parse_obj	parse_cylinder(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (parse_cylinder_base(p, &res.data.cylinder))
		res.type = TYPE_CYLINDER;
	return (res);
}

t_parse_obj	parse_cone(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (parse_cylinder_base(p, (t_cylinder *)&res.data.cone))
		res.type = TYPE_CONE;
	return (res);
}
