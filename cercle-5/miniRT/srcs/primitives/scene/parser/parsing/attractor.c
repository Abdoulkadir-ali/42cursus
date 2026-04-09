/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:50:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Parses a gravitational attractor: bh <pos> <mass>
 */
t_parse_obj	parse_attractor(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.attractor.pos))
		return (res);
	res.data.attractor.mass = parse_double(p);
	res.type = TYPE_ATTRACTOR;
	return (res);
}
